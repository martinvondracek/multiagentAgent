/* 
 * File:   CComport.h
 * Author: martin
 *
 * Created on Sobota, 2013, február 23, 13:36
 * 
 * comport connector
 */

#ifndef CCOMPORT_H
#define	CCOMPORT_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <ctime>
#include <ratio>
#include <chrono>

class CComport {
    int Cport,   //identifikátor pre komunikáciu
    error;

    struct termios new_port_settings,  //nastavenie pri pripájaní
    old_port_settings[22];

    char comport[20];  //názov portu
    int baudrate; //baudrate
public:
    CComport();
    CComport(const char *cp, int bd);
    int OpenComport(); // connects/opens comport
    int PollComport(unsigned char *buf, int size); //reades from comport
    int ReadByte(unsigned char *buf);
    int ReadNBytes(unsigned char *buf, int size); //reads N bytes or breaks after 300ms
    int ReadGyro(); // reads packet from gyroscope
    int SendByte(unsigned char byte); // sends byte
    int SendnBytes(unsigned char * byte, int size); //sends n bytes
    int SendBuf(unsigned char *buf, int size); //sends buffer
    void CloseComport();  //closes comport
    int IsCTSEnabled(int comport_number);
    ~CComport();
};

#endif	/* CCOMPORT_H */

