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

#include "Position.h"

#define PI 3.14159265

class Obstacle {
public:
    Obstacle(int id, int id_spustenia, int prekazka, int robot, float x_rob,
            float y_rob, float fi_rob, float x_p, float y_p, bool naraz_vpravo,
            bool naraz_vlavo, bool naraz_vpredu);
    Obstacle(int id, int id_spustenia, int prekazka, Position *poloha, bool naraz_vpravo,
            bool naraz_vlavo, bool naraz_vpredu);
    virtual ~Obstacle();
    
    const char * toJson();
    static Obstacle * fromJson(const char *json);
    const char * toString();
    
    float getDistance(Obstacle *p2);
    float getDistance(Position *p2);
    
    float GetFi_rob();
    void SetFi_rob(float fi_rob);
    int GetId();
    void SetId(int id);
    int GetId_mapping();
    void SetId_mapping(int id_spustenia);
    bool IsHitLeft();
    void SethitLeft(bool naraz_vlavo);
    bool IsHitRight();
    void SethitRight(bool naraz_vpravo);
    bool IsHitFront();
    void SetHitFront(bool naraz_vpredu);
    int GetObstacle(); // gets id of obstacle
    void SetObstacle(int prekazka);
    int GetRobot(); // gets id of agent
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

