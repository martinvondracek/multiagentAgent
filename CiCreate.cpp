/* 
 * File:   CiCreate.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 16:45
 */

#include "CiCreate.h"

CiCreate::CiCreate(komunikacia_shm *shm2) : agentClass(shm2) {
}

int CiCreate::Nastav_polohu(int x_0, int y_0, int uhol_0) {
    std::cout << "nastav polohu\n";
    return 0;
}

int CiCreate::Pohyb(WORD p, WORD l) {
    std::cout << "pohyb\n";
    return 0;
}

int CiCreate::Preskumaj_prostredie() {
    std::cout << "preskumaj prostredie\n";
    for (int i=0; i<20; i++) {
        std::cout << "preskumaj prostredie\n";
        usleep(1000*1000);
    }
    return 0;
}

CiCreate::~CiCreate() {
    std::cout << "destruktor CiCreate\n";
}

