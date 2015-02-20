/* 
 * File:   CiCreate.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 16:45
 */

#include "CiCreate.h"

#define PI 3.14159265

void *Odometria(void *arg) {
    odometria_shm * shm2 = (odometria_shm *) arg;
    
    // inicializujeme
    shm2->prejdena_vzdialenost = 0;
    shm2->prejdeny_uhol = 0;
    shm2->aktualny_uhol = 0;
    shm2->x_rel = 0;
    shm2->y_rel = 0;
    
    //cyklický update údajov
    while (!(shm2->ukonci_vlakno)) {
        shm2->crDef->UpdateSensorsStates();
        shm2->prejdena_vzdialenost += abs(shm2->crDef->getLastDistance());
        shm2->prejdeny_uhol += abs(shm2->crDef->getLastAngle());
        shm2->aktualny_uhol += shm2->crDef->getLastAngle();
        shm2->aktualny_uhol = shm2->aktualny_uhol % 360;
        if (shm2->aktualny_uhol < 0) {
            shm2->aktualny_uhol += 360;
        }
        shm2->x_rel += shm2->crDef->getLastDistance() * sin(shm2->aktualny_uhol * PI / 180) * -1;
        shm2->y_rel += shm2->crDef->getLastDistance() * cos(shm2->aktualny_uhol * PI / 180);
        if (shm2->crDef->getWall()) {
            shm2->stena = 1;
        } else {
            shm2->stena = 0;
        }
        if (shm2->crDef->getBumpLeft()) {
            if (shm2->crDef->getBumpRight()) {
                shm2->naraznik_vpredu = 1;
                shm2->naraznik_vlavo = 0;
                shm2->naraznik_vpravo = 0;
            } else {
                shm2->naraznik_vpredu = 0;
                shm2->naraznik_vlavo = 1;
                shm2->naraznik_vpravo = 0;
            }
        } else {
            if (shm2->crDef->getBumpRight()) {
                shm2->naraznik_vpredu = 0;
                shm2->naraznik_vlavo = 0;
                shm2->naraznik_vpravo = 1;
            } else {
                shm2->naraznik_vpredu = 0;
                shm2->naraznik_vlavo = 0;
                shm2->naraznik_vpravo = 0;
            }
        }
        shm2->signalSteny = shm2->crDef->getWallSingal();
        shm2->bateriaNapatie = shm2->crDef->getBatteryNapatie();
        shm2->bateriaTeplota = shm2->crDef->getBatteryTeplota();
        shm2->Wheelpdrop = shm2->crDef->getZdvihnutie();
        shm2->Cliff = shm2->crDef->getSchody();
        //výpis do terminálu
//        system("clear");
//        std::cout << "Celková prejdená vzdialenosť " << shm2->prejdena_vzdialenost << "\n";
//        std::cout << "celkový uhol " << shm2->prejdeny_uhol << "\n";
//        std::cout << "akt uhol " << shm2->aktualny_uhol << "\n";
//        std::cout << "x_rel " << shm2->x_rel << "\n";
//        std::cout << "y_rel " << shm2->y_rel << "\n";
//        std::cout << "akt uhol " << shm2->aktualny_uhol << "\n";
//        std::cout << "posledna vzdial " << shm2->crDef->getLastDistance() << "\n";
//        std::cout << "posledny uhol " << shm2->crDef->getLastAngle() << "\n";
//        std::cout << "naraznik vpredu " << shm2->naraznik_vpredu << "\n";
//        std::cout << "naraznik vlavo " << shm2->naraznik_vlavo << "\n";
//        std::cout << "naraznik vpravo " << shm2->naraznik_vpravo << "\n";
//        std::cout << "stena " << shm2->stena << "\n";
//        std::cout << "signal steny " << ((int) shm2->signalSteny) << "\n";
        
        usleep(40 * 1000);
    }
    pthread_exit(NULL);
}

void *teleriadenie(void *arg) {
    std::cout << "teleriadenie\n";
    param_tele *param = (param_tele *) arg;
    char buf [50];
    
    while(!(*(param->ukonci)) && (param->create->getConnectedComport())) {
        //vypiseme stavy snimacov
        sprintf(buf, "%d", param->create->getPolohaX());
        param->widget->xLabel->setText(buf);
        sprintf(buf, "%d", param->create->getPolohaY());
        param->widget->yLabel->setText(buf);
        sprintf(buf, "%d", param->create->getPolohaUhol());
        param->widget->zLabel->setText(buf);
        usleep(100*1000);
    }
    
    pthread_exit(NULL);
}

CiCreate::CiCreate(komunikacia_shm *shm2) : agentClass(shm2) {
}

int CiCreate::Nastav_polohu(int x_0, int y_0, int uhol_0) {
    std::cout << "nastav polohu\n";
    return 0;
}

int CiCreate::Pohyb(WORD p, WORD l) {
    std::cout << "pohyb\n";
    
    if (connectedComport) {
        this->crDef->SendToCreate((unsigned char) 0x91, (WORD) p, (WORD) l);
        return 0;
    } else {
        printf("Nemožno spustit pohyb, neni pripojený robot\n");
        return -1;
    }
    
    return -1;
}

int CiCreate::connectComport(const char * comport) {
    if (this->connectedComport) {
        std::cout << "uz je pripojeny\n";
        return -1;
    }
    
    this->comport = comport;
    this->crDef = new CiCreateDef(comport, BAUDRATE);
    this->connectedComport = (crDef->ConnectToPort() == 0) ? true : false;
    
    if (this->connectedComport) {
        // alokovanie pamete pre SHM odometrie
        shm_odo = new odometria_shm;
        shm_odo->crDef = crDef;
        //inicializačné príkazy
        crDef->SendToCreate((unsigned char) OI_START);
        crDef->SendToCreate((unsigned char) OI_FULL);
        crDef->UpdateSensorsStates();
        //inicializácia vlastností
        shm_odo->prejdena_vzdialenost = 0;
        shm_odo->aktualny_uhol = 0;
        shm_odo->prejdeny_uhol = 0;
        shm_odo->x_rel;
        shm_odo->y_rel;
        shm_odo->ukonci_vlakno = 0;
        // vytvorí vlákno pre odometriu
        pthread_attr_t parametre;
        if (pthread_attr_init(&parametre)) return -1;
        pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
        if (pthread_create(&vlaknoOdometria, &parametre, Odometria, (void*) shm_odo)) return -1;
        return 0;
    } else {
        return -1;
    }
    
}

int CiCreate::disConnectComport() {
    if (connectedComport) {
        Pohyb((WORD) 0, (WORD) 0);
        shm_odo->ukonci_vlakno = 1;
        usleep(100*1000);
        delete crDef;
        
        this->connectedComport = false;
        return 0;
    }
    return -1;
}

bool CiCreate::getConnectedComport() {
    return this->connectedComport;
}

int CiCreate::startTeleriadenie(void *widget) {
    stopTele = false;
    
    param_tele *param = new param_tele;
    param->ukonci = &stopTele;
    param->widget = shm_R_GUI->widget;
    param->create = (CiCreate *) shm_R_GUI->agent;
    
    // vytvorí vlákno pre teleriadenie
    pthread_attr_t parametre;
    if (pthread_attr_init(&parametre)) return -1;
    pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);
    if (pthread_create(&vlaknoTeleriadenie, &parametre, teleriadenie, (void*) param)) return -1;
    
    return 0;
}

int CiCreate::stopTeleriadenie() {
    stopTele = true;
    usleep(200*1000);
    return 1;
    //pthread_cancel(vlaknoTeleriadenie);
}

int CiCreate::Preskumaj_prostredie() {
    std::cout << "preskumaj prostredie\n";
    /*while (1) {
        if (shm_R_GUI->ukonci_ulohu == true) {
            break;
        }
        
        // todo fakove data
        polohaClass *poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 1.23, 2.34, 3.45);
        prekazkaClass *prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, 1.23, 2.34, 3.45, 1.23, 2.34, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        
        std::cout << "preskumaj prostredie\n";
        usleep(1000*1000);
    }*/
    polohaClass *poloha;
    prekazkaClass *prekazka;
    
    if (shm_R_GUI->agent_id == 1) {
        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, 0, 0);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        //usleep(1000 * 1000);
        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, 100, 0);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        //usleep(1000 * 1000);
        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, 200, 0);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        //usleep(1000 * 1000);
        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, 300, 0);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        //usleep(1000 * 1000);

        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, 400, 0);
        prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, 0, 400, 0, 0, 400, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        //usleep(1000 * 1000);

        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, -100, 400, 0);
        prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, -100, 400, 0, -100, 400, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        //usleep(1000 * 1000);

        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, -200, 400, 0);
        prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, -200, 400, 0, -200, 400, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        //usleep(1000 * 1000);

        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, -200, 500, 0);
        prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, -200, 500, 0, -200, 500, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        //usleep(1000 * 1000);

        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, -200, 600, 0);
        prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, -200, 600, 0, -200, 600, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        //usleep(1000 * 1000);

        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, -100, 600, 0);
        prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, -100, 600, 0, -100, 600, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        //usleep(1000 * 1000);

        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 700, 600, 0);
        prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, 700, 600, 0, 700, 600, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        //usleep(1000 * 1000);
    }
    
    if (shm_R_GUI->agent_id == 2) {
        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, 0, 0);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        //usleep(1000 * 1000);
        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, -100, 0);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        //usleep(1000 * 1000);
        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, -200, 0);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        //usleep(1000 * 1000);
        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, -300, 0);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        //usleep(1000 * 1000);

        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 0, -400, 0);
        prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, 0, -400, 0, 0, -400, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        //usleep(1000 * 1000);

        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, -100, -400, 0);
        prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, -100, -400, 0, -100, -400, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        //usleep(1000 * 1000);
    }
    
    return 0;
}

int CiCreate::getPolohaX() {
    return shm_odo->x_rel;
}

int CiCreate::getPolohaY() {
    return shm_odo->y_rel;
}

int CiCreate::getPolohaUhol() {
    return shm_odo->aktualny_uhol;
}

CiCreate::~CiCreate() {
    std::cout << "destruktor CiCreate\n";
    disConnectComport();
}

