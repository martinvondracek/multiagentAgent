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

#include "Position.h"
#include "Obstacle.h"

#define TOLERANCIA 400

class PositionsOfAgents {
public:
    PositionsOfAgents(int myId);
    
    void addOrUpdatePoloha(Position *poloha); //updates position of agnet if exists, otherwise creates new
    bool isNearOhterAgent(Position *mojaPoloha); // if some other agent is near
    bool isNearOhterAgent(Obstacle *mojaPrekazka);
    
    std::string toString();
    
    virtual ~PositionsOfAgents();
private:
    int myId;
    std::list<Position*> polohyList;
    std::mutex m;

};

#endif	/* POLOHYAGENTOV_H */

