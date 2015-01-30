/* 
 * File:   agentClass.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 9:02
 */

#include "agentClass.h"

void *vlaknoMapovanie(void *arg) {
    //todo implementovat
    std::cout << "vlakno mapovanie aaa\n";
    komunikacia_shm *shm_R_GUI = (komunikacia_shm *) arg;
    agentClass *agent = (agentClass *) shm_R_GUI->agent;
    shm_R_GUI->prebieha_uloha = true;
    shm_R_GUI->ukonci_ulohu = false;
    agent->Preskumaj_prostredie();
    shm_R_GUI->prebieha_uloha = false;
}

void *vlaknoPrijimanieDatServera(void *arg) {
    int n;
    
    komunikacia_shm *shm_R_GUI = (komunikacia_shm *) arg;
    while (1) {
        std::cout << "vlakno prijimanie\n";
        char jsonData[256];
        n = shm_R_GUI->socket->receiveJson(jsonData, 255);
        if (n > 0) { //musia byt prijate byty
            std::cout << "data=" << jsonData << "\n";
            //rozparsovat a vyhodnotit
            std::string ctype = socketUtilClass::parseClassTypeFromJson(jsonData);
            //todo ak treba pustit mapovanie tak pustime vlakno
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
            //todo ak pride poziadavka na ukoncenie mapovania
            if (ctype.compare("STOP_MAPOVANIE") == 0) {
                shm_R_GUI->ukonci_ulohu = true;
            }
            //todo ak pride poziadavka na ukoncenie agenta
        }
        usleep(300*1000);
    }
    
}

agentClass::agentClass(komunikacia_shm *shm_R_GUI) {
    this->shm_R_GUI = shm_R_GUI;
    this->socket = new socketClass();    
    this->shm_R_GUI->socket = this->socket;
    this->shm_R_GUI->vlaknoMapovanie = &(this->vlaknoMapovanie);
}

int agentClass::getComport() {
    return this->comport;
}

int agentClass::connectComport(int comport) {
    this->comport = comport;
    this->connectedComport = true;
    return 0;
}

int agentClass::disConnectComport() {
    if (connectedComport) {
        this->connectedComport = false;
    }
    return 0;
}

bool agentClass::getConnectedComport() {
    return this->connectedComport;
}

const char * agentClass::getHostName() {
    return this->hostName;
}

int agentClass::getPortNumber() {
    return this->portNumber;
}

int agentClass::connectIp(int portNumber, const char *hostName) {
    this->portNumber = portNumber;
    std::strcpy(this->hostName, hostName);
    
    socket->connectToServer(this->portNumber, this->hostName);
    if (socket->getConnected()) {
        char jsonData[256];
        socket->receiveJson(jsonData, 255);
        std::cout << jsonData << "\n";
        int id = socketUtilClass::parseAgentIdFromJson(jsonData);
        int idSpustenia = socketUtilClass::parseAgentIdSpusteniaFromJson(jsonData);
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

int agentClass::disConnectIp() {
    std::cout << "disConnectIp\n";
    // todo poposielat co treba
    // todo posleme serveru ze koncime
    // skoncime vlakno mapovania aj prijimania
    
    if (this->connectedIp) {
        if (shm_R_GUI->prebieha_uloha == true) {
            shm_R_GUI->ukonci_ulohu = true;
            std::cout << "ukoncujeme ulohu v disConnectIp\n";
            usleep(200 * 1000);
            pthread_cancel(vlaknoMapovanie);
        }
        shm_R_GUI->socket->sendJson("{\"CLASSTYPE\" : \"QUIT\"}");
        pthread_cancel(vlaknoPrijimanie);
    }
    
    socket->disconnect();
    if (! socket->getConnected()) {
        this->connectedIp = false;
    }
    return 0;
}

bool agentClass::getConnectedIp() {
    this->connectedIp = socket->getConnected();
    return this->connectedIp;
}

int agentClass::Nastav_polohu(int x_0, int y_0, int uhol_0) {
    return 0;
}

int agentClass::Pohyb(WORD p, WORD l) {
    return 0;
}

int agentClass::Preskumaj_prostredie() {
    while (1) {
        if (shm_R_GUI->ukonci_ulohu == true) {
            break;
        }
        std::cout << "preskumaj prostredie\n";
        usleep(1000*1000);
    }
    return 0;
}

agentClass::~agentClass() {
    std::cout << "destruktor agentClass\n";
    disConnectIp();
    disConnectComport();
}

