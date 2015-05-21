/* 
 * File:   Prekazky.h
 * Author: root
 *
 * Created on Nedeľa, 2015, marec 15, 13:07
 */

#ifndef PREKAZKY_H
#define	PREKAZKY_H

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <mutex>

#include "Obstacle.h"

#define MIN_DISTANCE 50

class Obstacles {
public:
    Obstacles();
    
    //int newIdPrekazky(komunikacia_shm *shm_R_GUI); // zo serveru zisti nove id prekazky
                        // ak neni pripojeny tak len inkrementuje
    int addObstacle(Obstacle *prekazka); //saves obstacle
    bool isNearOtherWithId(Obstacle *prekazka, int tolerancia); //zisti ci sa k zadanej prekazke nachadza v urcitej vzdialenosti ina s rovnakym id robota
    bool isNearOtherExceptId(Obstacle *prekazka, int tolerancia); //zisti ci sa k zadanej prekazke nachadza v urcitej vzdialenosti ina s odlisnym id robota
    Obstacle* nearestObstacleExceptId(Obstacle *prekazka);
    bool isNearAnyOther(Obstacle *prekazka, int tolerancia); //zisti ci sa k zadanej prekazke nachadza v urcitej vzdialenosti ina s lubovolnym id robota
    bool isNearAny(Position *poloha, int tolerancia);
    Obstacle* findNearest(Position *poloha); //najde najblizsiu prekazku k zadanej polohe
    
    std::string toString();
    
    virtual ~Obstacles();
private:
    std::list<Obstacle*> prekazkyList;
    Obstacle *lastPrekazka = nullptr;
    
    std::mutex m;
};

#endif	/* PREKAZKY_H */

