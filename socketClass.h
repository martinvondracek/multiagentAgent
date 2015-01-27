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
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

class socketClass {
public:
    socketClass();
    socketClass(int portNum, const char *hostname);
    virtual ~socketClass();
    
    int connectToServer(); // pripoji sa na socket
    int disconnect(); // odpoji sa zo socketu
    int sendJson(const char *jsonData);
    int receiveJson(char *buffer, int bufSize);
    
    bool getConnected();
    const char *getHostName();
    void setHostName(const char *hostname);
    int getPortNumber();
    void setPortNumber(int portNum);
    
    int test();
private:
    bool connected = false;
    int portNumber;
    char *hostName = new char[50];
    
    // todo ID agenta od servera
    
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
};

#endif	/* SOCKETCLASS_H */

