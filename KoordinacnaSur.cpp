/* 
 * File:   KoordinacnaSur.cpp
 * Author: root
 * 
 * Created on Štvrtok, 2015, apríl 2, 16:50
 */

#include "CoordinationPosition.h"

CoordinationPosition::CoordinationPosition(int x, int y) {
    this->x = x;
    this->y = y;
    this->valid = true;
}

CoordinationPosition::CoordinationPosition(int x, int y, bool valid) {
    this->x = x;
    this->y = y;
    this->valid = valid;
}

int CoordinationPosition::GetX() {
    return x;
}

int CoordinationPosition::GetY() {
    return y;
}

bool CoordinationPosition::isValid() {
    return valid;
}

void CoordinationPosition::setInvalid() {
    this->valid = false;
}

CoordinationPosition* CoordinationPosition::newInvalid() {
    return new CoordinationPosition(0, 0, false);
}

std::string CoordinationPosition::toJson(){
    std::string pom;
    
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"KOORDINACNA_SUR\"");
    
    json.append(",\n\"X\" : ");
    json.append(std::to_string(x));
    
    json.append(",\n\"Y\" : ");
    json.append(std::to_string(y));
    
    json.append(",\n\"VALID\" : ");
    json.append(valid ? "true" : "false");
    
    json.append("\n}\n");
        
    return json;
}

CoordinationPosition* CoordinationPosition::fromJson(std::string json) {
    int x;
    int y;
    int valid;
    
    rapidjson::Document document;
    document.Parse<0>(json.c_str());
    
    x = document["X"].GetInt();
    y = document["Y"].GetInt();
    valid = document["VALID"].GetBool();
    
    return new CoordinationPosition(x, y, valid);
}

std::string CoordinationPosition::toString(){
    return toJson();
}

CoordinationPosition::~CoordinationPosition() {
}

