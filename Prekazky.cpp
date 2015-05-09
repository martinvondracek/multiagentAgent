/* 
 * File:   Prekazky.cpp
 * Author: root
 * 
 * Created on Nedeľa, 2015, marec 15, 13:07
 */

#include "Prekazky.h"

Prekazky::Prekazky() {}

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

int Prekazky::addPrekazka(Prekazka *prekazka) {
    m.lock();
    // todo vytvorit clone
    if (lastPrekazka == nullptr) {
        lastPrekazka = prekazka;
        prekazkyList.push_back(prekazka);
    } else {
        // ukladame vzdy v niakej minimalnej vzdialenosti
        if (lastPrekazka->getVzdialenost(prekazka) > MIN_DISTANCE) {
            lastPrekazka = prekazka;
            prekazkyList.push_back(prekazka);
        }
    }
    
    m.unlock();
    return 1;
}

bool Prekazky::isNearOtherWithId(Prekazka *prekazka, int tolerancia) {
    m.lock();
    std::list<Prekazka*>::iterator i;
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getVzdialenost(prekazka)<=tolerancia && (*i)->GetPrekazka()==prekazka->GetPrekazka()) {
                m.unlock();
                return true;
            }
        }
    m.unlock();
    return false;
}

bool Prekazky::isNearOtherExceptId(Prekazka *prekazka, int tolerancia) {
    m.lock();
    std::list<Prekazka*>::iterator i;
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getVzdialenost(prekazka)<=tolerancia && (*i)->GetPrekazka()!=prekazka->GetPrekazka()) {
                std::cout << (*i)->GetPrekazka() << " " << prekazka->GetPrekazka() << " " << (*i)->getVzdialenost(prekazka)-tolerancia << "\n";
                m.unlock();
                return true;
            }
        }
    m.unlock();
    return false;
}

bool Prekazky::isNearAnyOther(Prekazka *prekazka, int tolerancia) {
    m.lock();
    std::list<Prekazka*>::iterator i;
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getVzdialenost(prekazka)<=tolerancia) {
                m.unlock();
                return true;
            }
        }
    m.unlock();
    return false;
}

bool Prekazky::isNearAny(Poloha *poloha, int tolerancia) {
    m.lock();
    std::list<Prekazka*>::iterator i;
        for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
            if ((*i)->getVzdialenost(poloha)<=tolerancia) {
                m.unlock();
                return true;
            }
        }
    m.unlock();
    return false;
}
    
std::string Prekazky::toString() {
    std::string str = "{\n";
    
    m.lock();
    std::list<Prekazka*>::iterator i;
    for (i = prekazkyList.begin(); i != prekazkyList.end(); ++i) {
        str.append((*i)->toString());
        str.append("\n");
    }
    str.append("}\n");
    m.unlock();
        
    return str;
}

Prekazky::~Prekazky() {
    m.lock();
    m.unlock();
}

