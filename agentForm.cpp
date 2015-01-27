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
    
    agent = new agentClass();
}

void agentForm::pripojComportClicked() {
    std::cout << "pripojComportClicked\n";
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

void agentForm::odpojComportClicked() {
    std::cout << "odpojComportClicked\n";
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

void agentForm::pripojServerClicked() {
    std::cout << "pripojServerClicked\n";
    
//    socket = new socketClass(widget.ipPortEdit->text().toInt(), widget.ipEdit->text().toStdString().c_str());
//    socket->connectToServer();
//    if (socket->getConnected()) {
//        connectedIp = true;
        
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
 //   }
    //        char buf[256];
//        socket->sendJson("nejaky string");
//        socket->receiveJson(buf, 255);
//        std::cout << buf << "\n";
}

void agentForm::odpojServerClicked() {
    std::cout << "odpojServerClicked\n";
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

void agentForm::nastavAktPolohuClicked() {
    std::cout << "nastavAktPolohuClicked\n";
}

void agentForm::dopreduClicked() {
    std::cout << "dopreduClicked\n";
}

void agentForm::zastavClicked() {
    std::cout << "zastavClicked\n";
}

void agentForm::dolavaClicked() {
    std::cout << "dolavaClicked\n";
}

void agentForm::dopravaClicked() {
    std::cout << "dopravaClicked\n";
}

agentForm::~agentForm() {
    std::cout << "destruktor agentForm\n";
    // todo implementovat
    odpojServerClicked();
    odpojComportClicked();
    delete agent;
}
