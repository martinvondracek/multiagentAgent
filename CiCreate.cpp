/* 
 * File:   CiCreate.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 16:45
 */

#include "CiCreate.h"

#define PI 3.14159265

void *Odometria(void *arg) {
    odometria_shm * shmO = (odometria_shm *) arg;
    
    // inicializujeme
    shmO->prejdena_vzdialenost = 0;
    shmO->prejdeny_uhol = 0;
    shmO->aktualny_uhol = 0;
    shmO->x_rel = 0;
    shmO->y_rel = 0;
    
    //cyklický update údajov
    while (!(shmO->ukonci_vlakno)) {
        shmO->mutCrdef.lock();
        auto t_start = std::chrono::high_resolution_clock::now();
        shmO->crDef->UpdateSensorsStates();
        shmO->prejdena_vzdialenost += abs(shmO->crDef->getLastDistance());
        shmO->prejdeny_uhol += abs(shmO->crDef->getLastAngle());
        shmO->aktualny_uhol += shmO->crDef->getLastAngle();
        shmO->aktualny_uhol = shmO->aktualny_uhol % 360;
        if (shmO->aktualny_uhol < 0) {
            shmO->aktualny_uhol += 360;
        }
        shmO->x_rel += shmO->crDef->getLastDistance() * sin(shmO->aktualny_uhol * PI / 180) * -1;
        shmO->y_rel += shmO->crDef->getLastDistance() * cos(shmO->aktualny_uhol * PI / 180);
        if (shmO->crDef->getWall()) {
            shmO->stena = 1;
        } else {
            shmO->stena = 0;
        }
        if (shmO->crDef->getBumpLeft()) {
            if (shmO->crDef->getBumpRight()) {
                shmO->naraznik_vpredu = 1;
                shmO->naraznik_vlavo = 0;
                shmO->naraznik_vpravo = 0;
            } else {
                shmO->naraznik_vpredu = 0;
                shmO->naraznik_vlavo = 1;
                shmO->naraznik_vpravo = 0;
            }
        } else {
            if (shmO->crDef->getBumpRight()) {
                shmO->naraznik_vpredu = 0;
                shmO->naraznik_vlavo = 0;
                shmO->naraznik_vpravo = 1;
            } else {
                shmO->naraznik_vpredu = 0;
                shmO->naraznik_vlavo = 0;
                shmO->naraznik_vpravo = 0;
            }
        }
        shmO->signalSteny = shmO->crDef->getWallSingal();
        shmO->bateriaNapatie = shmO->crDef->getBatteryNapatie();
        shmO->bateriaTeplota = shmO->crDef->getBatteryTeplota();
        shmO->Wheelpdrop = shmO->crDef->getZdvihnutie();
        shmO->Cliff = shmO->crDef->getSchody();
        shmO->mutCrdef.unlock();
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
        //shm2->crDef->UpdateSensorsStates();
        usleep(40 * 1000);
        //usleep(150 * 1000);
        auto t_end = std::chrono::high_resolution_clock::now();
        /*std::cout << "odometria Wall clock time passed: "
                << std::chrono::duration<double, std::milli>(t_end - t_start).count()
                << " ms\n";*/
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
    shm_odo->x_rel = x_0;
    shm_odo->y_rel = y_0;
    shm_odo->aktualny_uhol = uhol_0;
    std::cout << "nastav polohu\n";
    return 0;
}

int CiCreate::Pohyb(WORD p, WORD l) {
    //std::cout << "pohyb\n";
    
    if (connectedComport) {
        //saturujeme na min a max hodnoty rychlosti
        if (p < RIGHT_WHEEL_MAX_NEG_SPEED) p = RIGHT_WHEEL_MAX_NEG_SPEED;
        if (p > RIGHT_WHEEL_MAX_POS_SPEED) p = RIGHT_WHEEL_MAX_POS_SPEED;
        if (l < LEFT_WHEEL_MAX_NEG_SPEED) l = LEFT_WHEEL_MAX_NEG_SPEED;
        if (l > LEFT_WHEEL_MAX_POS_SPEED) l = LEFT_WHEEL_MAX_POS_SPEED;
        
        shm_odo->mutCrdef.lock();
        shm_odo->crDef->SendToCreate((unsigned char) 0x91, (WORD) p, (WORD) l);
        shm_odo->mutCrdef.unlock();
        return 0;
    } else {
        std::cout << "Nemožno spustit pohyb po naraz, neni pripojený robot\n";
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
    
    polohaClass *poloha;
    prekazkaClass *prekazka;
    
    while (1) {
        if (shm_R_GUI->ukonci_ulohu == true) {
            break;
        }
        poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, shm_odo->x_rel, shm_odo->y_rel, shm_odo->aktualny_uhol);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        // todo fakove data
//        polohaClass *poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 1.23, 2.34, 3.45);
//        prekazkaClass *prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, 1.23, 2.34, 3.45, 1.23, 2.34, 0, 0, 1);
//        shm_R_GUI->socket->sendJson(poloha->toJson());
//        shm_R_GUI->socket->sendJson(prekazka->toJson());
        
        std::cout << "preskumaj prostredie\n";
        usleep(200*1000);
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

void CiCreate::pokusy() {
    //Dopredu_po_naraz();
    Dopredu_o_vzdialenost_reg(100);
    usleep(1000 * 1000);
    Dopredu_o_vzdialenost_reg(500);
}

int CiCreate::Dopredu_po_naraz() {
    if (connectedComport) {
        Pohyb(120, 120);
        while (1) {
            if (shm_odo->naraznik_vpredu || shm_odo->naraznik_vlavo || shm_odo->naraznik_vpravo) {
                Pohyb(0, 0);
                break;
            }
            if (shm_odo->ukonci_vlakno) {
                Pohyb(0, 0);
                break;
            }
            usleep(10 * 1000);
        }
        return 1;
    } else {
        std::cout << "Nemožno spustit pohyb po naraz, neni pripojený robot\n";
        return 0;
    }
}

int CiCreate::Dopredu_o_vzdialenost(int ziad_vzdial) {
    //postupne zrýchluje a spomaluje aby sa zmenšila chyba prešmykovaním kolies
    if (connectedComport && shm_odo->ukonci_vlakno==0) {
        int poc_vzdial = shm_odo->prejdena_vzdialenost;
        // ak chceme prejst o vzdialenost vacsiu ako 200mm rozbiehame sa 
        // na 2 krat aby sme nepresmykovali, inak ideme len pomalsou rychlostou
        if (ziad_vzdial > 200) {
            ziad_vzdial += poc_vzdial;
            Pohyb(150, 150);
            while (1) {
                if (abs(shm_odo->prejdena_vzdialenost - poc_vzdial) > 10) {
                    break;
                }
                if (shm_odo->ukonci_vlakno) {
                    Pohyb(0, 0);
                    break;
                }
                usleep(10 * 1000);
            }
            Pohyb(250, 250);
        } else {
            ziad_vzdial += poc_vzdial;
            Pohyb(150, 150);
        }
        //cakame kym sa priblizime na 70mm
        while (1) {
            if (abs(shm_odo->prejdena_vzdialenost - ziad_vzdial) < 70) {
                break;
            }
            if (shm_odo->ukonci_vlakno) {
                Pohyb(0, 0);
                break;
            }
            usleep(10 * 1000);
        }
        //ked sme blizko zmensime rychlost aby sme sa presnejsie priblizili
        Pohyb(100, 100);
        while (1) {
            if (abs(shm_odo->prejdena_vzdialenost - ziad_vzdial) < 20) {
                break;
            }
            if (shm_odo->ukonci_vlakno) {
                Pohyb(0, 0);
                break;
            }
            usleep(10 * 1000);
        }
        //sme na mieste zastavime
        Pohyb(0, 0);
        return 1;
    } else {
        std::cout << "Nemožno spustit pohyb po naraz, neni pripojený robot\n";
        return 0;
    }
}

int CiCreate::Dopredu_o_vzdialenost_reg(int ziad_vzdial) {
    //postupne zrýchluje a potom regulatorom zastavi na pozadovanej vzdialenosti
    int K = 2;
    int rychl = 50;
    int akcZasah;
    
    if (connectedComport && shm_odo->ukonci_vlakno==0) {
        ziad_vzdial = abs(ziad_vzdial);
        int poc_vzdial = shm_odo->prejdena_vzdialenost;
        ziad_vzdial += poc_vzdial;
        
        // rozbiehame az dokedy sa nedostaneme na rychlost aktualneho akcneho zasahu
        int cyklus = 0;
        while (1) {
            cyklus++;
            rychl += 10*K;
            akcZasah = K*(ziad_vzdial - shm_odo->prejdena_vzdialenost);
            
            Pohyb((WORD) rychl, (WORD) rychl);
            
            if (rychl >= abs(akcZasah) || abs(rychl) > LEFT_WHEEL_MAX_POS_SPEED) {
                break;
            }
            
            if (shm_odo->ukonci_vlakno) {
                Pohyb(0, 0);
                break;
            }
            usleep(10 * 1000);
        }
        
        //brzdime
        while (1) {
            akcZasah = K*(ziad_vzdial - shm_odo->prejdena_vzdialenost);
            // min rychlost 50
            if (abs(akcZasah<50)) {
                if (akcZasah>0) akcZasah=50;
                if (akcZasah<0) akcZasah=-50;
            }
            
            Pohyb((WORD) akcZasah, (WORD) akcZasah);
            
            if (abs(shm_odo->prejdena_vzdialenost - ziad_vzdial) < 10) {
                break;
            }
            
            if (shm_odo->ukonci_vlakno) {
                Pohyb(0, 0);
                break;
            }
            usleep(10 * 1000);
        }
        //sme na mieste zastavime
        Pohyb(0, 0);
        return 1;
    } else {
        std::cout << "Nemožno spustit pohyb po naraz, neni pripojený robot\n";
        return 0;
    }
}

int CiCreate::Otocenie_o_uhol(int ziad_uhol, int smer) {
    // 0 doprava
    // 1 dolava
}

int CiCreate::Otocenie_o_uhol_reg(int ziad_uhol, int smer) {
    // 0 doprava
    // 1 dolava
}

int CiCreate::Sledovanie_steny() {
    
}

CiCreate::~CiCreate() {
    std::cout << "destruktor CiCreate\n";
    disConnectComport();
}

