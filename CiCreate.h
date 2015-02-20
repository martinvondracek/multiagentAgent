/* 
 * File:   CiCreate.h
 * Author: root
 *
 * Created on Utorok, 2015, január 27, 16:45
 */

#ifndef CICREATE_H
#define	CICREATE_H

#include "CiCreate.h"
#include "agentClass.h"
#include "CiCreateDef.h"
#include "agentForm.h"

struct odometria_shm {
    int bateriaNapatie;
    char bateriaTeplota;
    int id; //id robota
    int synchronizacia = 0; //premenná na synchronizáciu komunikácie
    int prejdena_vzdialenost = 0; //[mm]
    int prejdeny_uhol = 0; //[stupen]
    int aktualny_uhol = 0; //[stupen]
    int x_rel = 0; //[mm]
    int y_rel = 0; //[mm]
    CiCreateDef *crDef; //objekt na komunikáciu s iRobot Create
    int ukonci_vlakno = 0; //či má ukončiť vlákno pri rušení objektu
    int naraznik_vpredu = 0;
    int naraznik_vpravo = 0;
    int naraznik_vlavo = 0;
    int stena = 0; //či je prítomná stena
    int signalSteny = 0; //velkosť signálu steny
    
    unsigned char Cliff;
    unsigned char Wheelpdrop; //0-1
};

class CiCreate : public agentClass {
public:
    CiCreate(komunikacia_shm *shm2);
    virtual ~CiCreate();
    
    int connectComport(const char * comport);
    int disConnectComport();
    bool getConnectedComport();
    int startTeleriadenie(void *widget);
    int stopTeleriadenie();
    
    int Nastav_polohu(int x_0, int y_0, int uhol_0);
    int Pohyb(WORD p, WORD l);
    int Preskumaj_prostredie();
    
    int getPolohaX();
    int getPolohaY();
    int getPolohaUhol();
private:
    CiCreateDef *crDef;
    odometria_shm *shm_odo;
    pthread_t vlaknoOdometria;
    pthread_t vlaknoTeleriadenie;
    bool stopTele = false;
};

struct param_tele {
    bool *ukonci;
    CiCreate *create;
    Ui::agentForm *widget;
};

#endif	/* CICREATE_H */

