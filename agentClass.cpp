/* 
 * File:   agentClass.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 9:02
 */

#include "agentClass.h"

agentClass::agentClass() {
}

int agentClass::getComport() {
    return this->comport;
}

int agentClass::connectComport(int comport) {
    // todo implementovat
    this->comport = comport;
    this->connectedComport = true;
    return 0;
}

int agentClass::disConnectComport() {
    if (connectedComport) {
        // todo implementovat
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
    // todo implementovat
    this->portNumber = portNumber;
    std::strcpy(this->hostName, hostName);
    this->connectedIp = true;
    return 0;
}

int agentClass::disConnectIp() {
    if (connectedIp) {
        // todo implementovat
        this->connectedIp = false;
    }
    return 0;
}

bool agentClass::getConnectedIp() {
    return this->connectedIp;
}

agentClass::~agentClass() {
    std::cout << "destruktor agentClass\n";
    disConnectIp();
    disConnectComport();
}

