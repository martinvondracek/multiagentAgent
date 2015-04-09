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

class KoordinacnaSur {
public:
    KoordinacnaSur(int x, int y);
    
    int GetX();
    int GetY();    
    bool isValid();
    void setInvalid();
    
    static KoordinacnaSur* newInvalid();
    
    std::string toJson();
    static KoordinacnaSur* fromJson(std::string json);
    std::string toString();
    
    virtual ~KoordinacnaSur();
private:
    int x;
    int y;
    bool valid;
    
    KoordinacnaSur(int x, int y, bool valid);
};

#endif	/* KOORDINACNASUR_H */

