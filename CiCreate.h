/* 
 * File:   CiCreate.h
 * Author: root
 *
 * Created on Utorok, 2015, január 27, 16:45
 */

#ifndef CICREATE_H
#define	CICREATE_H

#include <mutex>

#include "CiCreate.h"
#include "Agent.h"
#include "CiCreateDef.h"
#include "agentForm.h"
#include "AkcnyZasah.h"

#define LEFT_WHEEL_MAX_POS_SPEED 250
#define LEFT_WHEEL_MAX_NEG_SPEED -250
#define RIGHT_WHEEL_MAX_POS_SPEED 250
#define RIGHT_WHEEL_MAX_NEG_SPEED -250

#define VZDIAL_POLOHY_POSLANIE 50
#define VZDIAL_PREKAZKY_POSLANIE 50

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
    CComport *gyroComport;
    int ukonci_vlakno = 0; //či má ukončiť vlákno pri rušení objektu
    int naraznik_vpredu = 0;
    int naraznik_vpravo = 0;
    int naraznik_vlavo = 0;
    int stena = 0; //či je prítomná stena
    int signalSteny = 0; //velkosť signálu steny
    bool wallFollowing = false;
    
    unsigned char Cliff;
    unsigned char Wheelpdrop; //0-1
    
    std::mutex mutCrdef;
};

class CiCreate : public Agent {
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
    
    int getSnimacSteny();
    bool isStena();
    bool isKolizia(); // vrati 1 ak je v kolizii (naraz) 0 ak neni
    
    void pokusy();
private:
    CiCreateDef *crDef;
    odometria_shm *shm_odo;
    pthread_t vlaknoOdometria;
    pthread_t vlaknoGyro;
    pthread_t vlaknoTeleriadenie;
    std::thread posielanieThread;
    bool stopTele = false;
    
    int uholKBodu(int x, int y);
    int Dopredu_po_naraz(); //pošle robot rovno až pokial nenarazí nárazníkom
    int Dopredu_o_vzdialenost(int ziad_vzdial); //prejde rovno o zadanú vzdialenosť
    int Dopredu_o_vzdialenost_reg(int ziad_vzdial); // regulatorom prejde rovno o zadanú vzdialenosť
    int Otocenie_o_uhol(int ziad_uhol, int smer); //otočí sa o zadaný uhol 0 doprava 1 dolava
    int Otocenie_o_uhol_reg(int ziad_uhol, int smer); //regulatorovo - otočí sa o zadaný uhol 0 doprava 1 dolava
    int Sledovanie_steny(); //ide rovno po náraz, obíde krabicu alebo prekážku
    int Chyt_stenu();
    int Sledovanie_steny_ciste(); //obíde krabicu alebo prekážku
    
    AkcnyZasah * obchadzanie(AkcnyZasah *zasah);
    AkcnyZasah * skumanie(AkcnyZasah *zasah);
    int Pohyb(AkcnyZasah *zasah);
};

struct param_tele {
    bool *ukonci;
    CiCreate *create;
    Ui::agentForm *widget;
};

#endif	/* CICREATE_H */

