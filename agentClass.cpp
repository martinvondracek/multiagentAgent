/* 
 * File:   agentClass.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 9:02
 */

#include "agentClass.h"

agentClass::agentClass(komunikacia_shm *shm_R_GUI) {
    this->shm_R_GUI = shm_R_GUI;
    this->socket = new socketClass();    
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
        int id = socketUtilClass::parseAgentIdFromJson(jsonData);
        if (id > 0) {
            shm_R_GUI->agent_id = id;
            this->connectedIp = true;
            std::cout << "mame id " << shm_R_GUI->agent_id << "\n";
            return 0;
        }
    }
    
    return -1;
}

int agentClass::disConnectIp() {
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
    return 0;
}

agentClass::~agentClass() {
    std::cout << "destruktor agentClass\n";
    disConnectIp();
    disConnectComport();
}

