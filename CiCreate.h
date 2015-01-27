/* 
 * File:   CiCreate.h
 * Author: root
 *
 * Created on Utorok, 2015, január 27, 16:45
 */

#ifndef CICREATE_H
#define	CICREATE_H

#include "agentClass.h"


class CiCreate : agentClass {
public:
    CiCreate(komunikacia_shm *shm2);
    virtual ~CiCreate();
private:

};

#endif	/* CICREATE_H */

