/* 
 * File:   socketClass.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, január 25, 19:09
 */

#include "SocketConnector.h"

SocketConnector::SocketConnector() {
}

bool SocketConnector::getConnected() {
    return this->connected;
}

const char * SocketConnector::getHostName() {
    return this->hostName;
}

int SocketConnector::getPortNumber() {
    return this->portNumber;
}

int SocketConnector::connectToServer(int portNum, const char *hostname) {
    this->portNumber = portNum;
    std::strcpy(this->hostName, hostname);
    std::cout << "connecting to server IP: " << hostName << ":" << portNumber << "\n";
    
    int n;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cout << "ERROR opening socket\n";
        return -1;
    }
    server = gethostbyname(hostName);
    if (server == NULL) {
        std::cout << "ERROR, no such host\n";
        return -1;
    }
    bzero((char *) &serv_addr, sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
            (char *) &serv_addr.sin_addr.s_addr,
            server->h_length);
    serv_addr.sin_port = htons(portNumber);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        std::cout << "ERROR connecting\n";
        return -1;
    }
    connected = true;
    std::cout << "connected to server IP: " << hostName << ":" << portNumber << "\n";
    return 0;
}

int SocketConnector::disconnect() {
    // odpojime zo socketu ak je pripojeny
    if (!connected) {
        return -1;
    }
    
    close(sockfd);
    connected = false;
    std::cout << "agent disconnected\n";
    return 0;
}

int SocketConnector::sendJson(const char *jsonData) {
    std::string str2 = jsonData;
    if (!connected) {
        return -1;
    }
    
    int n;
    
    std::string str = "";
    str.append(str2);
    str.append("KKK");
    const char *data = str.c_str();
    //std::cout << "posielam" << str << "\n" << data << "json" << jsonData << "\n";
    
    //m.lock();
    //n = write(sockfd, " ", strlen(" "));
    n = write(sockfd, data, strlen(data));
    usleep(10*1000);
    //m.unlock();
    
    if (n < 0) {
        std::cout << "ERROR writing to socket\n";
        return -1;
    }
    return n; // vratime pocet poslanych
}

int SocketConnector::receiveJson(char *buffer, int bufSize) {
    if (!connected) {
        return -1;
    }
    
    int n;
    
    bzero(buffer, bufSize);
    n = read(sockfd, buffer, bufSize);
    if (n < 0) {
        std::cout << "ERROR reading from socket\n";
        return n;
    }
    return n;
}

int SocketConnector::test() {
    if (!connected) {
        return -1;
    }
    char buf[256];
    sendJson("nejaky string");
    receiveJson(buf, 255);
    std::cout << buf << "\n";
    return 0;
    
}

SocketConnector::~SocketConnector() {
    std::cout << "destruktor socketClass\n";
    disconnect();
}

