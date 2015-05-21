/* 
 * File:   Prekazky.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, marec 15, 13:07
 */

#include "Obstacles.h"

Obstacles::Obstacles() {}

/*int Prekazky::newIdPrekazky(komunikacia_shm *shm_R_GUI) {
    m.lock();
    shm_R_GUI->isIdPrekazkyValid = false;
        if (shm_R_GUI->socket->getConnected()) {
            int lastIdPrekazky = shm_R_GUI->id_prekazky;
            shm_R_GUI->socket->sendJson(SocketUtil::createNewIdPrekazky());
            while (lastIdPrekazky==shm_R_GUI->id_prekazky && shm_R_GUI->ukonci_ulohu==false) {
                //pockame kym nam pride nove
                usleep(50*1000);
            }
            std::cout << "nove id prekazky: " << shm_R_GUI->id_prekazky << "\n";
        } else {
            //ak sme neni pripojení na server iba inkrementujeme
            shm_R_GUI->id_prekazky++;
            std::cout << "nove id prekazky: " << shm_R_GUI->id_prekazky << "\n";
        }
        shm_R_GUI->isIdPrekazkyValid = true;
    
    m.unlock();
    return shm_R_GUI->id_prekazky;
}*/

int Obstacles::addObstacle(Obstacle *prekazka) {
    m.lock();
    // todo vytvorit clone
    if (lastPrekazka == nullptr) {
        lastPrekazka = prekazka;
        prekazkyList.push_back(prekazka);
    } else {
        // ukladame vzdy v niakej minimalnej vzdialenosti
        if (lastPrekazka->getDistance(prekazka) > MIN_DISTANCE) {
            lastPrekazka = prekazka;
            prekazkyList.push_back(prekazka);
        }
    }
    
    m.unlock();
    return 1;
}

bool Obstacles::isNearOtherWithId(Obstacle *prekazka, int tolerancia) {
    m.lock();
    std::list<Obstacle*>::iterator i;
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getDistance(prekazka)<=tolerancia && (*i)->GetObstacle()==prekazka->GetObstacle()) {
                m.unlock();
                return true;
            }
        }
    m.unlock();
    return false;
}

bool Obstacles::isNearOtherExceptId(Obstacle *prekazka, int tolerancia) {
    m.lock();
    std::list<Obstacle*>::iterator i;
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getDistance(prekazka)<=tolerancia && (*i)->GetObstacle()!=prekazka->GetObstacle()) {
                std::cout << (*i)->GetObstacle() << " " << prekazka->GetObstacle() << " " << (*i)->getDistance(prekazka)-tolerancia << "\n";
                m.unlock();
                return true;
            }
        }
    m.unlock();
    return false;
}

Obstacle* Obstacles::nearestObstacleExceptId(Obstacle *prekazka) {
    m.lock();
    std::list<Obstacle*>::iterator i;
    Obstacle *nearest = *prekazkyList.begin();
    float vzdial = nearest->getDistance(prekazka);
    
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getDistance(prekazka)<vzdial && (*i)->GetObstacle()!=prekazka->GetObstacle()) {
                nearest = (*i);
                vzdial = (*i)->getDistance(prekazka);
            }
        }
    m.unlock();
    return nearest;
}

bool Obstacles::isNearAnyOther(Obstacle *prekazka, int tolerancia) {
    m.lock();
    std::list<Obstacle*>::iterator i;
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getDistance(prekazka)<=tolerancia) {
                m.unlock();
                return true;
            }
        }
    m.unlock();
    return false;
}

bool Obstacles::isNearAny(Position *poloha, int tolerancia) {
    m.lock();
    std::list<Obstacle*>::iterator i;
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getDistance(poloha)<=tolerancia) {
                m.unlock();
                return true;
            }
        }
    m.unlock();
    return false;
}

Obstacle* Obstacles::findNearest(Position *poloha) {
    m.lock();
    std::list<Obstacle*>::iterator i;
    Obstacle *nearest = *prekazkyList.begin();
    float vzdial = nearest->getDistance(poloha);
    
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getDistance(poloha)<vzdial) {
                nearest = (*i);
                vzdial = (*i)->getDistance(poloha);
            }
        }
    m.unlock();
    return nearest;
}
    
std::string Obstacles::toString() {
    std::string str = "{\n";
    
    m.lock();
    std::list<Obstacle*>::iterator i;
    for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
        str.append((*i)->toString());
        str.append("\n");
    }
    str.append("}\n");
    m.unlock();
        
    return str;
}

Obstacles::~Obstacles() {
    m.lock();
    m.unlock();
}

