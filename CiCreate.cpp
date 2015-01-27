/* 
 * File:   CiCreate.cpp
 * Author: root
 * 
 * Created on Utorok, 2015, január 27, 16:45
 */

#include "CiCreate.h"

CiCreate::CiCreate(komunikacia_shm *shm2) : agentClass(shm2) {
}

CiCreate::~CiCreate() {
    std::cout << "destruktor CiCreate\n";
}

