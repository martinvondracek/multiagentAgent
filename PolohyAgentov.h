/* 
 * File:   PolohyAgentov.h
 * Author: root
 *
 * Created on Štvrtok, 2015, marec 26, 16:39
 */

#ifndef POLOHYAGENTOV_H
#define	POLOHYAGENTOV_H

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <mutex>

#include "Poloha.h"
#include "Prekazka.h"

#define TOLERANCIA 400

class PolohyAgentov {
public:
    PolohyAgentov(int myId);
    
    void addOrUpdatePoloha(Poloha *poloha);
    bool isNearOhterAgent(Poloha *mojaPoloha);
    bool isNearOhterAgent(Prekazka *mojaPrekazka);
    
    std::string toString();
    
    virtual ~PolohyAgentov();
private:
    int myId;
    std::list<Poloha*> polohyList;
    std::mutex m;

};

#endif	/* POLOHYAGENTOV_H */

