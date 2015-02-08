/* 
 * File:   polohaClass.cpp
 * Author: root
 * 
 * Created on Sobota, 2015, január 24, 10:45
 */

#include "polohaClass.h"

polohaClass::polohaClass(int id, int id_spustenia, int robot, float x, float y, float fi) {
    this->id = id;
    this->id_spustenia = id_spustenia;
    this->robot = robot;
    this->x = x;
    this->y = y;
    this->fi = fi;
}

float polohaClass::GetFi() {
    return fi;
}

void polohaClass::SetFi(float fi) {
    this->fi = fi;
}

int polohaClass::GetId() {
    return id;
}

void polohaClass::SetId(int id) {
    this->id = id;
}

int polohaClass::GetId_spustenia() {
    return id_spustenia;
}

void polohaClass::SetId_spustenia(int id_spustenia) {
    this->id_spustenia = id_spustenia;
}

int polohaClass::GetRobot() {
    return robot;
}

void polohaClass::SetRobot(int robot) {
    this->robot = robot;
}

float polohaClass::GetX() {
    return x;
}

void polohaClass::SetX(float x) {
    this->x = x;
}

float polohaClass::GetY() {
    return y;
}

void polohaClass::SetY(float y) {
    this->y = y;
}

const char * polohaClass::toJson() {
    std::string pom;
    
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"POLOHACLASS\"");
    
    json.append(",\n\"ID\" : ");
    json.append(std::to_string(id));
    
    json.append(",\n\"ID_SPUSTENIA\" : ");
    json.append(std::to_string(id_spustenia));
    
    json.append(",\n\"ROBOT\" : ");
    json.append(std::to_string(robot));
    
    json.append(",\n\"X\" : ");
    pom = std::to_string(x);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"Y\" : ");
    pom = std::to_string(y);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"FI\" : ");
    pom = std::to_string(fi);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append("\n}\n");
        
    return json.c_str();
}

polohaClass * polohaClass::fromJson(const char *json) {
    int id;
    int id_spustenia;
    int robot;
    float x;
    float y;
    float fi;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    id = document["ID"].GetInt();
    id_spustenia = document["ID_SPUSTENIA"].GetInt();
    robot = document["ROBOT"].GetInt();
    x = document["X"].GetDouble();
    y = document["Y"].GetDouble();
    fi = document["FI"].GetDouble();
    
    return new polohaClass(id, id_spustenia, robot, x, y, fi);
}

const char * polohaClass::toString() {
    return toJson();
}

polohaClass::~polohaClass() {
}

