/* 
 * File:   PolohyAgentov.cpp
 * Author: root
 * 
 * Created on Štvrtok, 2015, marec 26, 16:39
 */

#include "PositionsOfAgents.h"

PositionsOfAgents::PositionsOfAgents(int myId) {
    this->myId = myId;
}

void PositionsOfAgents::addOrUpdatePoloha(Position *poloha) {
    m.lock();
    if (myId != poloha->GetRobot()) {
        //vymazeme stare a pridame nove
        std::list<Position*>::iterator i;
        for (i = polohyList.begin(); i != polohyList.end(); ++i) {
            if ((*i)->GetRobot() == poloha->GetRobot()) {
                polohyList.erase(i);
                break;
            }
        }
        polohyList.push_back(poloha);
    }
    m.unlock();
}

bool PositionsOfAgents::isNearOhterAgent(Position *mojaPoloha) {
    m.lock();
    bool isNear = false;
    std::list<Position*>::iterator i;
    for (i = polohyList.begin(); i != polohyList.end(); ++i) {
        if ((*i)->GetRobot()!=mojaPoloha->GetRobot() && (*i)->getDistance(mojaPoloha)<TOLERANCIA) {
            isNear = true;
            break;
        }
    }
    m.unlock();
    return isNear;
}

bool PositionsOfAgents::isNearOhterAgent(Obstacle *mojaPrekazka) {
    m.lock();
    bool isNear = false;
    std::list<Position*>::iterator i;
    for (i = polohyList.begin(); i != polohyList.end(); ++i) {
        //pouzijeme suradnice prekazky
        Position *pomPoloha = new Position(0, mojaPrekazka->GetId_mapping(),
                mojaPrekazka->GetRobot(), mojaPrekazka->GetX_p(),
                mojaPrekazka->GetY_p(), mojaPrekazka->GetFi_rob());
        if ((*i)->GetRobot()!=mojaPrekazka->GetRobot() && (*i)->getDistance(pomPoloha)<TOLERANCIA) {
            isNear = true;
            break;
        }
    }
    m.unlock();
    return isNear;
}

std::string PositionsOfAgents::toString() {
    std::string str = "{\n";
    
    m.lock();
    std::list<Position*>::iterator i;
    for (i = polohyList.begin(); i != polohyList.end(); ++i) {
        str.append((*i)->toString());
        str.append("\n");
    }
    str.append("}\n");
    m.unlock();
        
    return str;
}

PositionsOfAgents::~PositionsOfAgents() {
    m.lock();
    m.unlock();
}

