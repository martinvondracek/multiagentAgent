/* 
 * File:   polohaClass.h
 * Author: root
 *
 * Created on Sobota, 2015, január 24, 10:45
 */

#ifndef POLOHACLASS_H
#define	POLOHACLASS_H

#include <rapidjson/document.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <iostream>

class polohaClass {
public:
    polohaClass(int id, int id_spustenia, int robot, float x, float y, float fi);
    virtual ~polohaClass();
    
    const char * toJson();
    static polohaClass * fromJson(const char *json);
    const char * toString();
    
    float GetFi();
    void SetFi(float fi);
    int GetId();
    void SetId(int id);
    int GetId_spustenia();
    void SetId_spustenia(int id_spustenia);
    int GetRobot();
    void SetRobot(int robot);
    float GetX();
    void SetX(float x);
    float GetY();
    void SetY(float y);
private:
    int id;
    int id_spustenia;
    int robot;
    float x;
    float y;
    float fi;
};

#endif	/* POLOHACLASS_H */

