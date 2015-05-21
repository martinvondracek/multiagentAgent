/* 
 * File:   KoordinacnaSur.h
 * Author: root
 *
 * Created on Štvrtok, 2015, apríl 2, 16:50
 */

#ifndef KOORDINACNASUR_H
#define	KOORDINACNASUR_H

#include <rapidjson/document.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <iostream>

class CoordinationPosition {
public:
    CoordinationPosition(int x, int y);
    
    int GetX();
    int GetY();    
    bool isValid();
    void setInvalid();
    
    static CoordinationPosition* newInvalid();
    
    std::string toJson();
    static CoordinationPosition* fromJson(std::string json);
    std::string toString();
    
    virtual ~CoordinationPosition();
private:
    int x;
    int y;
    bool valid;
    
    CoordinationPosition(int x, int y, bool valid);
};

#endif	/* KOORDINACNASUR_H */

