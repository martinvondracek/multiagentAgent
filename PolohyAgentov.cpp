/* 
 * File:   PolohyAgentov.cpp
 * Author: root
 * 
 * Created on Štvrtok, 2015, marec 26, 16:39
 */

#include "PolohyAgentov.h"

PolohyAgentov::PolohyAgentov(int myId) {
    this->myId = myId;
}

void PolohyAgentov::addOrUpdatePoloha(Poloha *poloha) {
    m.lock();
    if (myId != poloha->GetRobot()) {
        //vymazeme stare a pridame nove
        std::list<Poloha*>::iterator i;
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

bool PolohyAgentov::isNearOhterAgent(Poloha *mojaPoloha) {
    m.lock();
    bool isNear = false;
    std::list<Poloha*>::iterator i;
    for (i = polohyList.begin(); i != polohyList.end(); ++i) {
        if ((*i)->GetRobot()!=mojaPoloha->GetRobot() && (*i)->getVzdialenost(mojaPoloha)<TOLERANCIA) {
            isNear = true;
            break;
        }
    }
    m.unlock();
    return isNear;
}

bool PolohyAgentov::isNearOhterAgent(Prekazka *mojaPrekazka) {
    m.lock();
    bool isNear = false;
    std::list<Poloha*>::iterator i;
    for (i = polohyList.begin(); i != polohyList.end(); ++i) {
        //pouzijeme suradnice prekazky
        Poloha *pomPoloha = new Poloha(0, mojaPrekazka->GetId_spustenia(),
                mojaPrekazka->GetRobot(), mojaPrekazka->GetX_p(),
                mojaPrekazka->GetY_p(), mojaPrekazka->GetFi_rob());
        if ((*i)->GetRobot()!=mojaPrekazka->GetRobot() && (*i)->getVzdialenost(pomPoloha)<TOLERANCIA) {
            isNear = true;
            break;
        }
    }
    m.unlock();
    return isNear;
}

std::string PolohyAgentov::toString() {
    std::string str = "{\n";
    
    m.lock();
    std::list<Poloha*>::iterator i;
    for (i = polohyList.begin(); i != polohyList.end(); ++i) {
        str.append((*i)->toString());
        str.append("\n");
    }
    str.append("}\n");
    m.unlock();
        
    return str;
}

PolohyAgentov::~PolohyAgentov() {
    m.lock();
    m.unlock();
}

