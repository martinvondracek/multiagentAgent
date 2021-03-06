/* 
 * File:   agentForm.h
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:36
 * 
 * GUI for agent
 */

#ifndef _AGENTFORM_H
#define	_AGENTFORM_H

#include <stdio.h>   
#include <unistd.h>
#include <iostream>
#include <thread>

#include "ui_agentForm.h"
#include "Agent.h"
#include "CiCreate.h"

class agentForm : public QDialog {
    Q_OBJECT
public slots:
    void pripojComportClicked(); //pripoji sa na comport
    void odpojComportClicked(); //odpoji sa z comport
    void pripojServerClicked(); //pripoji sa na server
    void odpojServerClicked(); //odpoji sa z server
    void nastavAktPolohuClicked(); //nastavi aktualne suradnice polohy
    void dopreduClicked(); //pohne robot dopredu
    void zastavClicked(); //zastavi robot
    void dolavaClicked(); //pohne robot dolava
    void dopravaClicked(); //pohne robot doprava
    void mapujClicked();
    void testClicked();
public:
    agentForm();
    virtual ~agentForm();
private:
    Ui::agentForm widget;
    
    Agent *agent;
    komunikacia_shm *shm_R_GUI;
    
    pthread_t threadTest; // TODO vymazat
};

#endif	/* _AGENTFORM_H */
