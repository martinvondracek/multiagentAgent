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
    void SetX(int x);
    int GetY();
    void SetY(int y);
    
    std::string toJson();
    static KoordinacnaSur* fromJson(std::string json);
    std::string toString();
    
    virtual ~KoordinacnaSur();
private:
    int x;
    int y;

};

#endif	/* KOORDINACNASUR_H */

