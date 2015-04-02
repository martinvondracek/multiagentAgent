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
}

int KoordinacnaSur::GetX() {
    return x;
}

void KoordinacnaSur::SetX(int x) {
    this->x = x;
}

int KoordinacnaSur::GetY() {
    return y;
}

void KoordinacnaSur::SetY(int y) {
    this->y = y;
}

std::string KoordinacnaSur::toJson(){
    std::string pom;
    
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"KOORDINACNA_SUR\"");
    
    json.append(",\n\"X\" : ");
    json.append(std::to_string(x));
    
    json.append(",\n\"Y\" : ");
    json.append(std::to_string(y));
    
    json.append("\n}\n");
        
    return json;
}

KoordinacnaSur* KoordinacnaSur::fromJson(std::string json) {
    int x;
    int y;
    
    rapidjson::Document document;
    document.Parse<0>(json.c_str());
    
    x = document["X"].GetInt();
    y = document["Y"].GetInt();
    
    return new KoordinacnaSur(x, y);
}

std::string KoordinacnaSur::toString(){
    return toJson();
}

KoordinacnaSur::~KoordinacnaSur() {
}

