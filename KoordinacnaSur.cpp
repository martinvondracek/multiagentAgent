/* 
 * File:   KoordinacnaSur.cpp
 * Author: root
 * 
 * Created on Štvrtok, 2015, apríl 2, 16:50
 */

#include "KoordinacnaSur.h"

KoordinacnaSur::KoordinacnaSur(int x, int y) {
    this->x = x;
    this->y = y;
    this->valid = true;
}

KoordinacnaSur::KoordinacnaSur(int x, int y, bool valid) {
    this->x = x;
    this->y = y;
    this->valid = false;
}

int KoordinacnaSur::GetX() {
    return x;
}

int KoordinacnaSur::GetY() {
    return y;
}

bool KoordinacnaSur::isValid() {
    return valid;
}

KoordinacnaSur* KoordinacnaSur::newInvalid() {
    return new KoordinacnaSur(0, 0, false);
}

std::string KoordinacnaSur::toJson(){
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

KoordinacnaSur* KoordinacnaSur::fromJson(std::string json) {
    int x;
    int y;
    int valid;
    
    rapidjson::Document document;
    document.Parse<0>(json.c_str());
    
    x = document["X"].GetInt();
    y = document["Y"].GetInt();
    valid = document["VALID"].GetBool();
    
    return new KoordinacnaSur(x, y, valid);
}

std::string KoordinacnaSur::toString(){
    return toJson();
}

KoordinacnaSur::~KoordinacnaSur() {
}

