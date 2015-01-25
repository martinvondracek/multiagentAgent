/* 
 * File:   socketClass.h
 * Author: root
 *
 * Created on Nedeľa, 2015, január 25, 19:09
 */

#ifndef SOCKETCLASS_H
#define	SOCKETCLASS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

class socketClass {
public:
    socketClass();
    socketClass(int portNum);
    virtual ~socketClass();
    
    int connectServer();
    int disconnect();
    int sendPacket();
    int receivePacket();
    int waitForClient();
    
    bool getConnected();
    int getPortNumber();
    void setPortNumber(int portNum);
    
    void test();
private:
    bool connected = false;
    int portNumber;
};

#endif	/* SOCKETCLASS_H */

