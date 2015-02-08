/* 
 * File:   prekazkaClass.h
 * Author: root
 *
 * Created on Sobota, 2015, január 24, 10:45
 */

#ifndef PREKAZKACLASS_H
#define	PREKAZKACLASS_H

#include <rapidjson/document.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <iostream>

class prekazkaClass {
public:
    prekazkaClass(int id, int id_spustenia, int prekazka, int robot, float x_rob,
            float y_rob, float fi_rob, float x_p, float y_p, bool naraz_vpravo,
            bool naraz_vlavo, bool naraz_vpredu);
    virtual ~prekazkaClass();
    
    const char * toJson();
    static prekazkaClass * fromJson(const char *json);
    const char * toString();
    
    float GetFi_rob();
    void SetFi_rob(float fi_rob);
    int GetId();
    void SetId(int id);
    int GetId_spustenia();
    void SetId_spustenia(int id_spustenia);
    bool IsNaraz_vlavo();
    void SetNaraz_vlavo(bool naraz_vlavo);
    bool IsNaraz_vpravo();
    void SetNaraz_vpravo(bool naraz_vpravo);
    bool IsNaraz_vpredu();
    void SetNaraz_vpredu(bool naraz_vpredu);
    int GetPrekazka();
    void SetPrekazka(int prekazka);
    int GetRobot();
    void SetRobot(int robot);
    float GetX_p();
    void SetX_p(float x_p);
    float GetX_rob();
    void SetX_rob(float x_rob);
    float GetY_p();
    void SetY_p(float y_p);
    float GetY_rob();
    void SetY_rob(float y_rob);
private:
    int id;
    int id_spustenia;
    int prekazka;
    int robot;
    float x_rob;
    float y_rob;
    float fi_rob;
    float x_p;
    float y_p;
    bool naraz_vpravo;
    bool naraz_vlavo;
    bool naraz_vpredu;
};

#endif	/* PREKAZKACLASS_H */

