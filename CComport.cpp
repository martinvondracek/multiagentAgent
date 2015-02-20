/* 
 * File:   CComport.cpp
 * Author: martin
 * 
 * Created on Sobota, 2013, február 23, 13:36
 */

#include "CComport.h"

CComport::CComport() {
    strcpy(comport, "/dev/rfcomm0");
    baudrate = B57600;
}

CComport::CComport(const char *cp, int bd) {
    strcpy(comport, cp);
    baudrate = bd;
}

int CComport::OpenComport() {
    Cport = open(comport, O_RDWR | O_NOCTTY | O_NDELAY);
    if (Cport == -1) {
        perror("unable to open comport ");
        return (1);
    }

    error = tcgetattr(Cport, old_port_settings);
    if (error == -1) {
        close(Cport);
        perror("unable to read portsettings ");
        return (1);
    }
    memset(&new_port_settings, 0, sizeof (new_port_settings)); /* clear the new struct */

    new_port_settings.c_cflag = baudrate | CS8 | CLOCAL | CREAD;
    new_port_settings.c_iflag = IGNPAR;
    new_port_settings.c_oflag = 0;
    new_port_settings.c_lflag = 0;
    new_port_settings.c_cc[VMIN] = 0; /* block untill n bytes are received */
    new_port_settings.c_cc[VTIME] = 0; /* block untill a timer expires (n * 100 mSec.) */
    error = tcsetattr(Cport, TCSANOW, &new_port_settings);
    if (error == -1) {
        close(Cport);
        perror("unable to adjust portsettings ");
        return (1);
    }

    return (0);
}

int CComport::PollComport(unsigned char *buf, int size) {
    int n;

#ifndef __STRICT_ANSI__    /* __STRICT_ANSI__ is defined when the -ansi option is used for gcc */
    if (size > SSIZE_MAX) size = (int) SSIZE_MAX; /* SSIZE_MAX is defined in limits.h */
#else
    if (size > 4096) size = 4096;
#endif

    n = read(Cport, buf, size);
    usleep(10 * 1000);

    return (n);
}

int CComport::SendByte(unsigned char byte) {
    int n;

    n = write(Cport, &byte, 1);
    if (n < 0) return (0);
    usleep(3 * 1000);

    return (n);
}

int CComport::SendnBytes(unsigned char * byte, int size) {
    int n;

    n = write(Cport, byte, size);
    if (n < 0) return (0);
    usleep(10 * 1000);

    return (n);
}

int CComport::SendBuf(unsigned char *buf, int size) {
    return (write(Cport, buf, size));
}

void CComport::CloseComport() {
    close(Cport);
    tcsetattr(Cport, TCSANOW, old_port_settings);
}

/*
 * Constant  Description
 * TIOCM_LE  DSR (data set ready/line enable)
 * TIOCM_DTR DTR (data terminal ready)
 * TIOCM_RTS RTS (request to send)
 * TIOCM_ST  Secondary TXD (transmit)
 * TIOCM_SR  Secondary RXD (receive)
 * TIOCM_CTS CTS (clear to send)
 * TIOCM_CAR DCD (data carrier detect)
 * TIOCM_CD  Synonym for TIOCM_CAR
 * TIOCM_RNG RNG (ring)
 * TIOCM_RI  Synonym for TIOCM_RNG
 * TIOCM_DSR DSR (data set ready)
 */

int CComport::IsCTSEnabled(int comport_number) {
    int status;

    status = ioctl(Cport, TIOCMGET, &status);

    if (status & TIOCM_CTS) return (1);
    else return (0);
}

CComport::~CComport() {
    std::cout << "destruktor CComport\n";
    CloseComport();
}

