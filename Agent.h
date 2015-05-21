/* 
 * File:   agentClass.h
 * Author: root
 *
 * Created on Utorok, 2015, január 27, 9:02
 * 
 * for agent functionality
 */

#ifndef AGENTCLASS_H
#define	AGENTCLASS_H

#define BAUDRATE B57600
//#define BAUDRATE B9600

#include <mutex>

#include "SocketConnector.h"
#include "SocketUtil.h"
#include "Agent.h"
#include "ui_agentForm.h"
#include "Position.h"
#include "Obstacle.h"
#include "Obstacles.h"
#include "PositionsOfAgents.h"
#include "CoordinationPosition.h"
//#include "agentForm.h"

typedef short int WORD;

struct komunikacia_shm {
    int agent_id;
    int id_spustenia;
    int id_prekazky = 0;
    bool isIdPrekazkyValid = false;
    Obstacles *prekazky;
    PositionsOfAgents *polohy;
    CoordinationPosition *koorSur;
    
    SocketConnector *socket;
    pthread_t *vlaknoMapovanie;
    void *agent; // (agentClass *)
    Ui::agentForm *widget;
    void *agentForm;
    
    bool prebieha_uloha = false;
    bool ukonci_ulohu = false; // či má ukončiť prehladávie
    
    std::mutex mutSocket;
};

class Agent {
public:
    Agent(komunikacia_shm *shm2);
    virtual ~Agent();
    
    const char * getComport();
    virtual int connectComport(const char * comport); // connects to iRobot Create
    virtual int disConnectComport();
    virtual bool getConnectedComport();
    virtual int startTeleriadenie(void *widget); //starts telecontrol - showing position in gui
    virtual int stopTeleriadenie();
    
    const char *getHostName();
    int getPortNumber();
    int connectIp(int portNumber, const char *hostName); // connects to server
    int disConnectIp();
    bool getConnectedIp();
    
    virtual int set_position(int x_0, int y_0, int uhol_0); // sets actual position of agent
    virtual int move(WORD p, WORD l); // moves agent with welocities p, l
    virtual int explore_environment(); // explores unknown environment
    
    virtual bool isInColision(); // if agent is in colision - bumper, cliff, wheel drop 
    
    virtual void pokusy();
    
protected:
    bool connectedComport = false;
    bool connectedIp = false;
    bool mappingNow = false;
    komunikacia_shm *shm_R_GUI; //SHM pre komunikáciu medzi robtom a GUI - ukoncenie ulohy
    SocketConnector *socket;
    
    pthread_t vlaknoPrijimanie; //prijimanie sprav zo servera
    pthread_t vlaknoMapovanie;
    
    const char * comport;
    int portNumber;
    char *hostName = new char[50];
    
private:
    
};

#endif	/* AGENTCLASS_H */

