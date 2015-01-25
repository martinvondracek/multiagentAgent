/* 
 * File:   socketClass.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, január 25, 19:09
 */

#include "socketClass.h"

socketClass::socketClass() {
    this->portNumber = 17005;
}

socketClass::socketClass(int portNum) {
    this->portNumber = portNum;
}

bool socketClass::getConnected() {
    return this->connected;
}

int socketClass::getPortNumber() {
    return this->portNumber;
}

void socketClass::setPortNumber(int portNum) {
    this->portNumber = portNum;
}

int socketClass::connectServer() {
    std::cout << "starting socket localhost, port: " << portNumber << "\n";
    
    // TODO implementovat
    connected = true;
    return -1;
}

void socketClass::test() {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    //portno = widget.ipPortEdit->text().toInt();
    portno = 17005;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) std::cout << "ERROR opening socket";
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
            (char *) &serv_addr.sin_addr.s_addr,
            server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) std::cout << "ERROR connecting";
    //printf("Please enter the message: ");
    //bzero(buffer, 256);
    //fgets(buffer, 255, stdin);
    //n = write(sockfd, buffer, strlen(buffer));
    n = write(sockfd, "nejaky string", strlen("nejaky string"));
    if (n < 0) std::cout << "ERROR writing to socket";
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0) std::cout << "ERROR reading from socket";
    printf("%s\n", buffer);
    close(sockfd);
}

socketClass::~socketClass() {
    std::cout << "destruktor socketClass\n";
}

