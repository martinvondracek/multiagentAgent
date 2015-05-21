/* 
 * File:   polohaClass.cpp
 * Author: root
 * 
 * Created on Sobota, 2015, január 24, 10:45
 */

#include "Position.h"

Position::Position(int id, int id_spustenia, int robot, float x, float y, float fi) {
    this->id = id;
    this->id_spustenia = id_spustenia;
    this->robot = robot;
    this->x = x;
    this->y = y;
    this->fi = fi;
}

float Position::GetFi() {
    return fi;
}

void Position::SetFi(float fi) {
    this->fi = fi;
}

int Position::GetId() {
    return id;
}

void Position::SetId(int id) {
    this->id = id;
}

int Position::GetId_mapping() {
    return id_spustenia;
}

void Position::SetId_mapping(int id_spustenia) {
    this->id_spustenia = id_spustenia;
}

int Position::GetRobot() {
    return robot;
}

void Position::SetRobot(int robot) {
    this->robot = robot;
}

float Position::GetX() {
    return x;
}

void Position::SetX(float x) {
    this->x = x;
}

float Position::GetY() {
    return y;
}

void Position::SetY(float y) {
    this->y = y;
}

const char * Position::toJson() {
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

Position * Position::fromJson(const char *json) {
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
    
    return new Position(id, id_spustenia, robot, x, y, fi);
}

const char * Position::toString() {
    return toJson();
}

float Position::getDistance(Position *p2) {
    return sqrt((x-p2->GetX())*(x-p2->GetX()) + (y-p2->GetY())*(y-p2->GetY()));
}

float Position::getDistance(CoordinationPosition *koorSur) {
    return sqrt((x-koorSur->GetX())*(x-koorSur->GetX()) + (y-koorSur->GetY())*(y-koorSur->GetY()));
}

Position::~Position() {
}

