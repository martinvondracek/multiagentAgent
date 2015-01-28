/* 
 * File:   CiCreate.h
 * Author: root
 *
 * Created on Utorok, 2015, január 27, 16:45
 */

#ifndef CICREATE_H
#define	CICREATE_H

#include "agentClass.h"


class CiCreate : public agentClass {
public:
    CiCreate(komunikacia_shm *shm2);
    virtual ~CiCreate();
    
    int Nastav_polohu(int x_0, int y_0, int uhol_0);
    int Pohyb(WORD p, WORD l);
    int Preskumaj_prostredie();
private:

};

#endif	/* CICREATE_H */

