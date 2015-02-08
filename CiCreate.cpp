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
    while (1) {
        if (shm_R_GUI->ukonci_ulohu == true) {
            break;
        }
        
        // todo fakove data
        polohaClass *poloha = new polohaClass(0, shm_R_GUI->id_spustenia, shm_R_GUI->agent_id, 1.23, 2.34, 3.45);
        prekazkaClass *prekazka = new prekazkaClass(0, shm_R_GUI->id_spustenia, 0, shm_R_GUI->agent_id, 1.23, 2.34, 3.45, 1.23, 2.34, 0, 0, 1);
        shm_R_GUI->socket->sendJson(poloha->toJson());
        usleep(10*1000);
        shm_R_GUI->socket->sendJson(prekazka->toJson());
        
        std::cout << "preskumaj prostredie\n";
        usleep(1000*1000);
    }
    return 0;
}

CiCreate::~CiCreate() {
    std::cout << "destruktor CiCreate\n";
}

