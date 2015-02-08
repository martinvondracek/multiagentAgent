/* 
 * File:   prekazkaClass.cpp
 * Author: root
 * 
 * Created on Sobota, 2015, január 24, 10:45
 */

#include "prekazkaClass.h"

prekazkaClass::prekazkaClass(int id, int id_spustenia, int prekazka, int robot,
        float x_rob, float y_rob, float fi_rob, float x_p, float y_p,
        bool naraz_vpravo, bool naraz_vlavo, bool naraz_vpredu) {
    this->id = id;
    this->id_spustenia = id_spustenia;
    this->prekazka = prekazka;
    this->robot = robot;
    this->x_rob = x_rob;
    this->y_rob = y_rob;
    this->fi_rob = fi_rob;
    this->x_p = x_p;
    this->y_p = y_p;
    this->naraz_vpravo = naraz_vpravo;
    this->naraz_vlavo = naraz_vlavo;
    this->naraz_vpredu = naraz_vpredu;
}

float prekazkaClass::GetFi_rob() {
    return fi_rob;
}

void prekazkaClass::SetFi_rob(float fi_rob) {
    this->fi_rob = fi_rob;
}

int prekazkaClass::GetId() {
    return id;
}

void prekazkaClass::SetId(int id) {
    this->id = id;
}

int prekazkaClass::GetId_spustenia() {
    return id_spustenia;
}

void prekazkaClass::SetId_spustenia(int id_spustenia) {
    this->id_spustenia = id_spustenia;
}

bool prekazkaClass::IsNaraz_vlavo() {
    return naraz_vlavo;
}

void prekazkaClass::SetNaraz_vlavo(bool naraz_vlavo) {
    this->naraz_vlavo = naraz_vlavo;
}

bool prekazkaClass::IsNaraz_vpravo() {
    return naraz_vpravo;
}

void prekazkaClass::SetNaraz_vpravo(bool naraz_vpravo) {
    this->naraz_vpravo = naraz_vpravo;
}

bool prekazkaClass::IsNaraz_vpredu() {
    return naraz_vpredu;
}

void prekazkaClass::SetNaraz_vpredu(bool naraz_vpredu) {
    this->naraz_vpredu = naraz_vpredu;
}

int prekazkaClass::GetPrekazka() {
    return prekazka;
}

void prekazkaClass::SetPrekazka(int prekazka) {
    this->prekazka = prekazka;
}

int prekazkaClass::GetRobot() {
    return robot;
}

void prekazkaClass::SetRobot(int robot) {
    this->robot = robot;
}

float prekazkaClass::GetX_p() {
    return x_p;
}

void prekazkaClass::SetX_p(float x_p) {
    this->x_p = x_p;
}

float prekazkaClass::GetX_rob() {
    return x_rob;
}

void prekazkaClass::SetX_rob(float x_rob) {
    this->x_rob = x_rob;
}

float prekazkaClass::GetY_p() {
    return y_p;
}

void prekazkaClass::SetY_p(float y_p) {
    this->y_p = y_p;
}

float prekazkaClass::GetY_rob() {
    return y_rob;
}

void prekazkaClass::SetY_rob(float y_rob) {
    this->y_rob = y_rob;
}

const char * prekazkaClass::toJson() {
    std::string pom;
    
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"PREKAZKACLASS\"");
    
    json.append(",\n\"ID\" : ");
    json.append(std::to_string(id));
    
    json.append(",\n\"ID_SPUSTENIA\" : ");
    json.append(std::to_string(id_spustenia));
    
    json.append(",\n\"PREKAZKA\" : ");
    json.append(std::to_string(prekazka));
    
    json.append(",\n\"ROBOT\" : ");
    json.append(std::to_string(robot));
    
    json.append(",\n\"X_ROB\" : ");
    pom = std::to_string(x_rob);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"Y_ROB\" : ");
    pom = std::to_string(y_rob);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"FI_ROB\" : ");
    pom = std::to_string(fi_rob);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"X_P\" : ");
    pom = std::to_string(x_p);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"Y_P\" : ");
    pom = std::to_string(y_p);
    std::replace( pom.begin(), pom.end(), ',', '.');
    json.append(pom);
    
    json.append(",\n\"NARAZ_VPRAVO\" : ");
    json.append(naraz_vpravo ? "true" : "false");
    
    json.append(",\n\"NARAZ_VLAVO\" : ");
    json.append(naraz_vlavo ? "true" : "false");
    
    json.append(",\n\"NARAZ_VPREDU\" : ");
    json.append(naraz_vpredu ? "true" : "false");
    
    json.append("\n}\n");
        
    return json.c_str();
}

prekazkaClass * prekazkaClass::fromJson(const char *json) {
    int id;
    int id_spustenia;
    int prekazka;
    int robot;
    float x_rob;
    float y_rob;
    float fi_rob;
    float x_p;
    float y_p;
    bool naraz_vpravo;
    bool naraz_vlavo;
    bool naraz_vpredu;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    id = document["ID"].GetInt();
    id_spustenia = document["ID_SPUSTENIA"].GetInt();
    prekazka = document["PREKAZKA"].GetInt();
    robot = document["ROBOT"].GetInt();
    x_rob = document["X_ROB"].GetDouble();
    y_rob = document["Y_ROB"].GetDouble();
    fi_rob = document["FI_ROB"].GetDouble();
    x_p = document["X_P"].GetDouble();
    y_p = document["Y_P"].GetDouble();
    naraz_vpravo = document["NARAZ_VPRAVO"].GetBool();
    naraz_vlavo = document["NARAZ_VLAVO"].GetBool();
    naraz_vpredu = document["NARAZ_VPREDU"].GetBool();
    
    return new prekazkaClass(id, id_spustenia, prekazka, robot, x_rob, y_rob, fi_rob, x_p, y_p, naraz_vpravo, naraz_vlavo, naraz_vpredu);
}

const char * prekazkaClass::toString() {
    return toJson();
}

prekazkaClass::~prekazkaClass() {
}

