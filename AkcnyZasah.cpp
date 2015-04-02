/* 
 * File:   AkcnyZasah.cpp
 * Author: root
 * 
 * Created on Štvrtok, 2015, apríl 2, 16:36
 */

#include "AkcnyZasah.h"

AkcnyZasah::AkcnyZasah(int rightWheel, int leftWheel, bool obchadzanie) {
    this->rightWheel = rightWheel;
    this->leftWheel = leftWheel;
    this->obchadzanie = obchadzanie;
}

int AkcnyZasah::GetLeftWheel() {
    return leftWheel;
}

void AkcnyZasah::SetLeftWheel(int leftWheel) {
    this->leftWheel = leftWheel;
}

bool AkcnyZasah::IsObchadzanie() {
    return obchadzanie;
}

void AkcnyZasah::SetObchadzanie(bool obchadzanie) {
    this->obchadzanie = obchadzanie;
}

int AkcnyZasah::GetRightWheel() {
    return rightWheel;
}

void AkcnyZasah::SetRightWheel(int rightWheel) {
    this->rightWheel = rightWheel;
}

AkcnyZasah* AkcnyZasah::stopWithObchadzanie() {
    return new AkcnyZasah(0, 0, true);
}

AkcnyZasah* AkcnyZasah::stopNotObchadzanie() {
    return new AkcnyZasah(0, 0, false);
}

AkcnyZasah::~AkcnyZasah() {
}

