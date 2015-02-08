/* 
 * File:   agentClass.h
 * Author: root
 *
 * Created on Utorok, 2015, január 27, 9:02
 */

#ifndef AGENTCLASS_H
#define	AGENTCLASS_H

#define BAUDRATE B57600

#include "socketClass.h"
#include "socketUtilClass.h"
#include "agentClass.h"
#include "ui_agentForm.h"

typedef short int WORD;

struct komunikacia_shm {
    int agent_id;
    int id_spustenia;
    socketClass *socket;
    pthread_t *vlaknoMapovanie;
    void *agent; // (agentClass *)
    Ui::agentForm *widget;
    void *agentForm;
    
    bool prebieha_uloha = false;
    bool ukonci_ulohu = false; // či má ukončiť prehladávie
};

class agentClass {
public:
    agentClass(komunikacia_shm *shm2);
    virtual ~agentClass();
    
    int getComport();
    int connectComport(int comport); // pripoji sa na robota
    int disConnectComport();
    bool getConnectedComport();
    
    const char *getHostName();
    int getPortNumber();
    int connectIp(int portNumber, const char *hostName); // pripoji sa k serveru
    int disConnectIp();
    bool getConnectedIp();
    
    virtual int Nastav_polohu(int x_0, int y_0, int uhol_0);
    virtual int Pohyb(WORD p, WORD l);
    virtual int Preskumaj_prostredie();
    
protected:
    bool connectedComport = false;
    bool connectedIp = false;
    bool mappingNow = false;
    komunikacia_shm *shm_R_GUI; //SHM pre komunikáciu medzi robtom a GUI - ukoncenie ulohy
    socketClass *socket;
    
    pthread_t vlaknoPrijimanie; //prijimanie sprav zo servera
    pthread_t vlaknoMapovanie;
    
    int comport;
    int portNumber;
    char *hostName = new char[50];
    
private:
    
};

#endif	/* AGENTCLASS_H */

