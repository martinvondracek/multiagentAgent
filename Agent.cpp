/* 
 * File:   agentClass.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 9:02
 */

#include "Agent.h"
#include "agentForm.h"

void *vlaknoMapovanie(void *arg) {
    std::cout << "vlakno mapovanie aaa\n";
    komunikacia_shm *shm_R_GUI = (komunikacia_shm *) arg;
    Agent *agent = (Agent *) shm_R_GUI->agent;
    shm_R_GUI->prebieha_uloha = true;
    shm_R_GUI->ukonci_ulohu = false;
    shm_R_GUI->id_prekazky = 0;
    shm_R_GUI->isIdPrekazkyValid = false;
    agent->Preskumaj_prostredie();
    shm_R_GUI->prebieha_uloha = false;
}

void *vlaknoObsluzenieServerQuit(void *arg) {
    // ked server posle ze konci tak sa od neho odpojime
    std::cout << "vlakno obsluzenie skoncenia servera\n";
    usleep(300*1000);
    agentForm *aagentForm = (agentForm *) arg;
    aagentForm->odpojServerClicked();
    //usleep(300*1000);
}

void *vlaknoPrijimanieDatServera(void *arg) {
    int n;
    
    komunikacia_shm *shm_R_GUI = (komunikacia_shm *) arg;
    Agent *agent = (Agent *) shm_R_GUI->agent;
    
    while (1) {
        //std::cout << "vlakno prijimanie\n";
        char jsonData[50001];
        bzero(jsonData, 50000);
        n = shm_R_GUI->socket->receiveJson(jsonData, 50000);
        if (n > 0) { //musia byt prijate byty
            //std::cout << "data=" << jsonData << "\n";
            
            //ak pride viacej dat naraz tak ich rozdelime
            std::string s = jsonData;
            std::string delimiter = "KKK";
            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                //std::cout << "data=" << jsonData << "\n";
                //std::cout << "data token=" << token << "=KONIEC\n";

                //rozparsovat a vyhodnotit
                std::string ctype = SocketUtil::parseClassTypeFromJson(token.c_str());
                //std::cout << "prislo ctype=" << ctype << "\n";
                //ak treba pustit mapovanie tak pustime nove vlakno
                if (ctype.compare("SPUSTIT_MAPOVANIE") == 0) {
                    pthread_attr_t parametre;
                    if (pthread_attr_init(&parametre)) {
                        std::cout << "chyba v attr_init\n";
                        continue;
                    }
                    pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
                    if (pthread_create(shm_R_GUI->vlaknoMapovanie, &parametre, vlaknoMapovanie, (void*) shm_R_GUI)) {
                        std::cout << "chyba vo vytvarani vlakna na prijimanie\n";
                        continue;
                    }
                }
                //todo ak pride koordinacna suradnica pre mapovanie
                if (ctype.compare("KOORDINACNA_SURADNICA") == 0) {
                    // TODO implementovat
                }
                //ak pride poziadavka na ukoncenie mapovania
                if (ctype.compare("STOP_MAPOVANIE") == 0) {
                    shm_R_GUI->ukonci_ulohu = true;
                }
                //ak pride ze konci server - odpojime
                if (ctype.compare("SERVER_QUIT") == 0) {
                    shm_R_GUI->ukonci_ulohu = true;

                    pthread_t thr1;
                    pthread_attr_t parametre;
                    if (pthread_attr_init(&parametre)) {
                        std::cout << "chyba v attr_init\n";
                    }
                    pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
                    if (pthread_create(&thr1, &parametre, vlaknoObsluzenieServerQuit, (void*) shm_R_GUI->agentForm)) {
                        std::cout << "chyba vo vytvarani vlakna na odpojenie\n";
                    }
                    return 0;
                }
                // ak pride nove ID spustenia
                if (ctype.compare("ID_SPUSTENIA") == 0) {
                    int id_p = SocketUtil::parseIdSpusteniaFromJson(token.c_str());
                    if (id_p > 0) {
                        shm_R_GUI->id_spustenia = id_p;
                        std::cout << "id spustenia=" << shm_R_GUI->id_spustenia << "\n";
                    }
                }
                // ak pride nove ID prekazky
                if (ctype.compare("NEW_ID_PREKAZKY") == 0) {
                    int id_p = SocketUtil::parseNewIdPrekazkyFromJson(token.c_str());
                    shm_R_GUI->id_prekazky = id_p;
                }
                // ak pride prekazka ulozime ju k ostatnym
                if (ctype.compare("PREKAZKACLASS") == 0) {
                    Prekazka *prekazka = Prekazka::fromJson(token.c_str());
                    shm_R_GUI->prekazky->addPrekazka(prekazka);
                    //std::cout << "prisla prekazka od:" <<  prekazka->GetRobot() << "\n";
                }
                // ak pride poloha ulozime ju k ostatnym
                if (ctype.compare("POLOHACLASS") == 0) {
                    Poloha *poloha = Poloha::fromJson(token.c_str());
                    // todo ulozime polohu ineho robota
                    //std::cout << "prisla poloha od:" <<  poloha->GetRobot() << "\n";
                }
                s.erase(0, pos + delimiter.length());
            }
        }
        usleep(300*1000);
    }
    
}

Agent::Agent(komunikacia_shm *shm_R_GUI) {
    this->shm_R_GUI = shm_R_GUI;
    this->socket = new SocketConnector();    
    this->shm_R_GUI->socket = this->socket;
    this->shm_R_GUI->vlaknoMapovanie = &(this->vlaknoMapovanie);
}

const char * Agent::getComport() {
    return this->comport;
}

int Agent::connectComport(const char * comport) {
    this->comport = comport;
    this->connectedComport = true;
    return 0;
}

int Agent::disConnectComport() {
    if (connectedComport) {
        this->connectedComport = false;
    }
    return 0;
}

bool Agent::getConnectedComport() {
    return this->connectedComport;
}

int Agent::startTeleriadenie(void *widget) {
    return 0;
}

int Agent::stopTeleriadenie() {
    return 0;
}

const char * Agent::getHostName() {
    return this->hostName;
}

int Agent::getPortNumber() {
    return this->portNumber;
}

int Agent::connectIp(int portNumber, const char *hostName) {
    this->portNumber = portNumber;
    std::strcpy(this->hostName, hostName);
    
    socket->connectToServer(this->portNumber, this->hostName);
    if (socket->getConnected()) {
        char jsonData[1001];
        socket->receiveJson(jsonData, 1000);
        //std::cout << jsonData << "\n";
        
        std::string s = jsonData;
        std::string delimiter = "KKK";
        size_t pos = 0;
        std::string token;
        pos = s.find(delimiter);
        token = s.substr(0, pos);
        
        int id = SocketUtil::parseAgentIdFromJson(token.c_str());
        int idSpustenia = SocketUtil::parseAgentIdSpusteniaFromJson(token.c_str());
        if (id>0 && idSpustenia>0) {
            shm_R_GUI->agent_id = id;
            shm_R_GUI->id_spustenia = idSpustenia;
            std::cout << "mame id " << shm_R_GUI->agent_id << ", id_spustenia " << shm_R_GUI->id_spustenia << "\n";
            // vytvorime nove vlakno na prijimanie zo socketu
            pthread_attr_t parametre;
            if (pthread_attr_init(&parametre)) {
                std::cout << "chyba v attr_init\n";
                return -1;
            }
            pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
            if (pthread_create(&(vlaknoPrijimanie), &parametre, vlaknoPrijimanieDatServera, (void*) shm_R_GUI)) {
                std::cout << "chyba vo vytvarani vlakna na prijimanie\n";
                return -1;
            }
            this->connectedIp = true;
            return 0;
        }
    }
    socket->disconnect();
    return -1;
}

int Agent::disConnectIp() {
    std::cout << "disConnectIp\n";
    // poposielat co treba
    // posleme serveru ze koncime
    // skoncime vlakno mapovania aj prijimania
    
    if (this->connectedIp) {
        if (shm_R_GUI->prebieha_uloha == true) {
            shm_R_GUI->ukonci_ulohu = true;
            std::cout << "ukoncujeme ulohu v disConnectIp\n";
            usleep(200 * 1000);
            pthread_cancel(vlaknoMapovanie);
        }
        shm_R_GUI->socket->sendJson(SocketUtil::createQuit(shm_R_GUI->agent_id));
        pthread_cancel(vlaknoPrijimanie);
    }
    
    socket->disconnect();
    if (! socket->getConnected()) {
        this->connectedIp = false;
    }
    return 0;
}

bool Agent::getConnectedIp() {
    this->connectedIp = socket->getConnected();
    return this->connectedIp;
}

int Agent::Nastav_polohu(int x_0, int y_0, int uhol_0) {
    return 0;
}

int Agent::Pohyb(WORD p, WORD l) {
    return 0;
}

int Agent::Preskumaj_prostredie() {
    while (1) {
        if (shm_R_GUI->ukonci_ulohu == true) {
            break;
        }
        std::cout << "preskumaj prostredie\n";
        usleep(1000*1000);
    }
    return 0;
}

void Agent::pokusy() {
    
}

bool Agent::isKolizia() {
    return false;
}

Agent::~Agent() {
    std::cout << "destruktor agentClass\n";
    disConnectIp();
    disConnectComport();
}

