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
#include <mutex>

class SocketConnector {
public:
    SocketConnector();
    virtual ~SocketConnector();
    
    int connectToServer(int portNum, const char *hostname); // pripoji sa na socket
    int disconnect(); // odpoji sa zo socketu
    int sendJson(const char *jsonData);
    int receiveJson(char *buffer, int bufSize);
    
    bool getConnected();
    const char *getHostName();
    int getPortNumber();
    
    int test();
private:
    bool connected = false;
    int portNumber = 17005;
    char *hostName = new char[50];
    std::mutex m;
    
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
};

#endif	/* SOCKETCLASS_H */

