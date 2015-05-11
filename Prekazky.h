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

#include "Prekazka.h"

#define MIN_DISTANCE 50

class Prekazky {
public:
    Prekazky();
    
    //int newIdPrekazky(komunikacia_shm *shm_R_GUI); // zo serveru zisti nove id prekazky
                        // ak neni pripojeny tak len inkrementuje
    int addPrekazka(Prekazka *prekazka); //ulozi prekazku
    bool isNearOtherWithId(Prekazka *prekazka, int tolerancia); //zisti ci sa k zadanej prekazke nachadza v urcitej vzdialenosti ina s rovnakym id robota
    bool isNearOtherExceptId(Prekazka *prekazka, int tolerancia); //zisti ci sa k zadanej prekazke nachadza v urcitej vzdialenosti ina s odlisnym id robota
    bool isNearAnyOther(Prekazka *prekazka, int tolerancia); //zisti ci sa k zadanej prekazke nachadza v urcitej vzdialenosti ina s lubovolnym id robota
    bool isNearAny(Poloha *poloha, int tolerancia);
    Prekazka* findNearest(Poloha *poloha); //najde najblizsiu prekazku k zadanej polohe
    
    std::string toString();
    
    virtual ~Prekazky();
private:
    std::list<Prekazka*> prekazkyList;
    Prekazka *lastPrekazka = nullptr;
    
    std::mutex m;
};

#endif	/* PREKAZKY_H */

