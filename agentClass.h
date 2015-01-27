/* 
 * File:   agentClass.h
 * Author: root
 *
 * Created on Utorok, 2015, január 27, 9:02
 */

#ifndef AGENTCLASS_H
#define	AGENTCLASS_H

#define BAUDRATE B57600

#include "../DP_server/polohaClass.h"
#include "../DP_server/prekazkaClass.h"

class agentClass {
public:
    agentClass();
    virtual ~agentClass();
    
    int getComport();
    int connectComport(int comport);
    int disConnectComport();
    bool getConnectedComport();
    
    const char *getHostName();
    int getPortNumber();
    int connectIp(int portNumber, const char *hostName);
    int disConnectIp();
    bool getConnectedIp();
    
private:
    bool connectedComport = false;
    bool connectedIp = false;
    
    int comport;
    int portNumber;
    char *hostName = new char[50];
};

#endif	/* AGENTCLASS_H */

