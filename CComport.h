/* 
 * File:   CComport.h
 * Author: martin
 *
 * Created on Sobota, 2013, február 23, 13:36
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
    int OpenComport(); // pripojí sa na port
    int PollComport(unsigned char *buf, int size); //číta z portu
    int ReadNBytes(unsigned char *buf, int size); //precita n bytov, caka kym ich neni taky pocet
                                                    // alebo neprejde 1 sekunda
    int SendByte(unsigned char byte); // pošle byte
    int SendnBytes(unsigned char * byte, int size); //pošle n bytov
    int SendBuf(unsigned char *buf, int size); //pošle buffer
    void CloseComport();  //zatvorí port
    int IsCTSEnabled(int comport_number);
    ~CComport();
};

#endif	/* CCOMPORT_H */

