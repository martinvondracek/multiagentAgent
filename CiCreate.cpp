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
    return 0;
}

int CiCreate::Pohyb(WORD p, WORD l) {
    return 0;
}

int CiCreate::Preskumaj_prostredie() {
    return 0;
}

CiCreate::~CiCreate() {
    std::cout << "destruktor CiCreate\n";
}

