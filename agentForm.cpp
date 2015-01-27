/*
 * File:   agentForm.cpp
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:36
 */

#include "agentForm.h"

agentForm::agentForm() {
    widget.setupUi(this);
    widget.comportEdit->setText("COM1");
    widget.ipEdit->setText("localhost");
    widget.ipPortEdit->setText("17005");
    widget.infoLabel->setText("");
    
    widget.odpojComportButton->setEnabled(false);
    widget.pripojServerButton->setEnabled(false);
    widget.odpojServerButton->setEnabled(false);
    widget.ipEdit->setEnabled(false);
    widget.ipPortEdit->setEnabled(false);
    widget.nastavAktPolohuButton->setEnabled(false);
    widget.x0Edit->setEnabled(false);
    widget.y0Edit->setEnabled(false);
    widget.z0Edit->setEnabled(false);
    widget.dopreduButton->setEnabled(false);
    widget.dopravaButton->setEnabled(false);
    widget.dolavaButton->setEnabled(false);
    widget.zastavButton->setEnabled(false);
    
    shm_R_GUI = new komunikacia_shm;
    shm_R_GUI->prebieha_uloha = 0;
    shm_R_GUI->ukonci_ulohu = 0;
    //agent = new agentClass(shm_R_GUI);
    agent = new CiCreate(shm_R_GUI);
}

void agentForm::pripojComportClicked() {
    std::cout << "pripojComportClicked\n";
    
    agent->connectComport(widget.comportEdit->text().toInt());
    if (agent->getConnectedComport()) {
        widget.infoLabel->setText("Robot pripojeny");
        widget.pripojComportButton->setEnabled(false);
        widget.odpojComportButton->setEnabled(true);
        widget.comportEdit->setEnabled(false);
        widget.pripojServerButton->setEnabled(true);
        widget.odpojServerButton->setEnabled(false);
        widget.ipEdit->setEnabled(true);
        widget.ipPortEdit->setEnabled(true);
        widget.nastavAktPolohuButton->setEnabled(true);
        widget.x0Edit->setEnabled(true);
        widget.y0Edit->setEnabled(true);
        widget.z0Edit->setEnabled(true);
        widget.dopreduButton->setEnabled(true);
        widget.dopravaButton->setEnabled(true);
        widget.dolavaButton->setEnabled(true);
        widget.zastavButton->setEnabled(true);
    }
    
}

void agentForm::odpojComportClicked() {
    std::cout << "odpojComportClicked\n";
    
    agent->disConnectComport();
    if (! agent->getConnectedComport()) {
        widget.infoLabel->setText("Robot odpojeny");
        widget.pripojComportButton->setEnabled(true);
        widget.odpojComportButton->setEnabled(false);
        widget.comportEdit->setEnabled(true);
        widget.pripojServerButton->setEnabled(false);
        widget.odpojServerButton->setEnabled(false);
        widget.ipEdit->setEnabled(false);
        widget.ipPortEdit->setEnabled(false);
        widget.nastavAktPolohuButton->setEnabled(false);
        widget.x0Edit->setEnabled(false);
        widget.y0Edit->setEnabled(false);
        widget.z0Edit->setEnabled(false);
        widget.dopreduButton->setEnabled(false);
        widget.dopravaButton->setEnabled(false);
        widget.dolavaButton->setEnabled(false);
        widget.zastavButton->setEnabled(false);
    }
    
}

void agentForm::pripojServerClicked() {
    std::cout << "pripojServerClicked\n";
    
    agent->connectIp(widget.ipPortEdit->text().toInt(), widget.ipEdit->text().toStdString().c_str());
    if (agent->getConnectedIp()) {    
        widget.infoLabel->setText("Pripojeny k serveru");
        widget.odpojComportButton->setEnabled(false);
        widget.pripojServerButton->setEnabled(false);
        widget.odpojServerButton->setEnabled(true);
        widget.ipEdit->setEnabled(false);
        widget.ipPortEdit->setEnabled(false);
        widget.nastavAktPolohuButton->setEnabled(false);
        widget.x0Edit->setEnabled(false);
        widget.y0Edit->setEnabled(false);
        widget.z0Edit->setEnabled(false);
        widget.dopreduButton->setEnabled(false);
        widget.dopravaButton->setEnabled(false);
        widget.dolavaButton->setEnabled(false);
        widget.zastavButton->setEnabled(false);
    }
    
}

void agentForm::odpojServerClicked() {
    std::cout << "odpojServerClicked\n";
    
    agent->disConnectIp();
    if (! agent->getConnectedIp()) {
        widget.infoLabel->setText("Odpojeny od serveru");
        widget.odpojComportButton->setEnabled(true);
        widget.pripojServerButton->setEnabled(true);
        widget.odpojServerButton->setEnabled(false);
        widget.ipEdit->setEnabled(true);
        widget.ipPortEdit->setEnabled(true);
        widget.nastavAktPolohuButton->setEnabled(true);
        widget.x0Edit->setEnabled(true);
        widget.y0Edit->setEnabled(true);
        widget.z0Edit->setEnabled(true);
        widget.dopreduButton->setEnabled(true);
        widget.dopravaButton->setEnabled(true);
        widget.dolavaButton->setEnabled(true);
        widget.zastavButton->setEnabled(true);
    }
    
}

void agentForm::nastavAktPolohuClicked() {
    std::cout << "nastavAktPolohuClicked\n";
    
    if (!agent->getConnectedComport()) {
        std::cout << "neni pripojeny\n";
        return;
    }
    
    int x,y,fi;
    x = widget.x0Edit->text().toInt();
    y = widget.y0Edit->text().toInt();
    fi = widget.z0Edit->text().toInt();
    agent->Nastav_polohu(x, y, fi);
}

void agentForm::dopreduClicked() {
    std::cout << "dopreduClicked\n";
    
    if (!agent->getConnectedComport()) {
        std::cout << "neni pripojeny\n";
        return;
    }
    
    agent->Pohyb(250, 250);
}

void agentForm::zastavClicked() {
    std::cout << "zastavClicked\n";
    
    if (!agent->getConnectedComport()) {
        std::cout << "neni pripojeny\n";
        return;
    }
    
    agent->Pohyb(0, 0);
}

void agentForm::dolavaClicked() {
    std::cout << "dolavaClicked\n";
    
    if (!agent->getConnectedComport()) {
        std::cout << "neni pripojeny\n";
        return;
    }
    
    agent->Pohyb(100, -100);
}

void agentForm::dopravaClicked() {
    std::cout << "dopravaClicked\n";
    
    if (!agent->getConnectedComport()) {
        std::cout << "neni pripojeny\n";
        return;
    }
    
    agent->Pohyb(-100, 100);
}

agentForm::~agentForm() {
    std::cout << "destruktor agentForm\n";
    zastavClicked();
    odpojServerClicked();
    odpojComportClicked();
    delete agent;
}
