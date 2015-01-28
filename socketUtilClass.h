/* 
 * File:   socketUtilClass.h
 * Author: root
 *
 * Created on Streda, 2015, január 28, 10:26
 */

#ifndef SOCKETUTILCLASS_H
#define	SOCKETUTILCLASS_H

#include <rapidjson/document.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <iostream>

class socketUtilClass {
public:
    socketUtilClass();
    virtual ~socketUtilClass();
    
    static int parseAgentIdFromJson(const char *json);
private:

};

#endif	/* SOCKETUTILCLASS_H */

