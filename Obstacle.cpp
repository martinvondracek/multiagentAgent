/* 
 * File:   prekazkaClass.cpp
 * Author: root
 * 
 * Created on Sobota, 2015, január 24, 10:45
 */

#include "Obstacle.h"

Obstacle::Obstacle(int id, int id_spustenia, int prekazka, int robot,
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

Obstacle::Obstacle(int id, int id_spustenia, int prekazka, Position *poloha, bool naraz_vpravo,
            bool naraz_vlavo, bool naraz_vpredu) {
    this->id = id;
    this->id_spustenia = id_spustenia;
    this->prekazka = prekazka;
    this->robot = poloha->GetRobot();
    this->x_rob = poloha->GetX();
    this->y_rob = poloha->GetY();
    this->fi_rob = poloha->GetFi();
    this->x_p = poloha->GetX();
    this->y_p = poloha->GetY();
    
    //upravime polohu prekazky na presnu polohu
    if (naraz_vpredu) {
        this->x_p += 170 * sin(this->fi_rob * PI / 180) * -1;
        this->y_p += 170 * cos(this->fi_rob * PI / 180);
    }
    if (naraz_vpravo) {
        int pomUhol = this->fi_rob - 45;
        pomUhol = pomUhol % 360;
        if (pomUhol < 0) {
            pomUhol += 360;
        }
        
        this->x_p += 170 * sin(pomUhol * PI / 180) * -1;
        this->y_p += 170 * cos(pomUhol * PI / 180);
    }
    if (naraz_vlavo) {
        int pomUhol = this->fi_rob - 45;
        pomUhol = pomUhol % 360;
        if (pomUhol < 0) {
            pomUhol += 360;
        }
        
        this->x_p += 170 * sin(pomUhol * PI / 180) * -1;
        this->y_p += 170 * cos(pomUhol * PI / 180);
    }
    
    //ak ideme iba podla senzoru steny (neni ziaden naraznik aktivovany)
    if (naraz_vpravo==false && naraz_vlavo==false && naraz_vpredu==false) {
        int pomUhol = this->fi_rob - 90;
        pomUhol = pomUhol % 360;
        if (pomUhol < 0) {
            pomUhol += 360;
        }
        
        this->x_p += 170 * sin(pomUhol * PI / 180) * -1;
        this->y_p += 170 * cos(pomUhol * PI / 180);
    }
    
    this->naraz_vpravo = naraz_vpravo;
    this->naraz_vlavo = naraz_vlavo;
    this->naraz_vpredu = naraz_vpredu;
}

float Obstacle::GetFi_rob() {
    return fi_rob;
}

void Obstacle::SetFi_rob(float fi_rob) {
    this->fi_rob = fi_rob;
}

int Obstacle::GetId() {
    return id;
}

void Obstacle::SetId(int id) {
    this->id = id;
}

int Obstacle::GetId_mapping() {
    return id_spustenia;
}

void Obstacle::SetId_mapping(int id_spustenia) {
    this->id_spustenia = id_spustenia;
}

bool Obstacle::IsHitLeft() {
    return naraz_vlavo;
}

void Obstacle::SethitLeft(bool naraz_vlavo) {
    this->naraz_vlavo = naraz_vlavo;
}

bool Obstacle::IsHitRight() {
    return naraz_vpravo;
}

void Obstacle::SethitRight(bool naraz_vpravo) {
    this->naraz_vpravo = naraz_vpravo;
}

bool Obstacle::IsHitFront() {
    return naraz_vpredu;
}

void Obstacle::SetHitFront(bool naraz_vpredu) {
    this->naraz_vpredu = naraz_vpredu;
}

int Obstacle::GetObstacle() {
    return prekazka;
}

void Obstacle::SetObstacle(int prekazka) {
    this->prekazka = prekazka;
}

int Obstacle::GetRobot() {
    return robot;
}

void Obstacle::SetRobot(int robot) {
    this->robot = robot;
}

float Obstacle::GetX_p() {
    return x_p;
}

void Obstacle::SetX_p(float x_p) {
    this->x_p = x_p;
}

float Obstacle::GetX_rob() {
    return x_rob;
}

void Obstacle::SetX_rob(float x_rob) {
    this->x_rob = x_rob;
}

float Obstacle::GetY_p() {
    return y_p;
}

void Obstacle::SetY_p(float y_p) {
    this->y_p = y_p;
}

float Obstacle::GetY_rob() {
    return y_rob;
}

void Obstacle::SetY_rob(float y_rob) {
    this->y_rob = y_rob;
}

const char * Obstacle::toJson() {
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

Obstacle * Obstacle::fromJson(const char *json) {
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
    
    return new Obstacle(id, id_spustenia, prekazka, robot, x_rob, y_rob, fi_rob, x_p, y_p, naraz_vpravo, naraz_vlavo, naraz_vpredu);
}

const char * Obstacle::toString() {
    return toJson();
}

float Obstacle::getDistance(Obstacle *p2) {
    return sqrt((x_p-p2->GetX_p())*(x_p-p2->GetX_p()) + (y_p-p2->GetY_p())*(y_p-p2->GetY_p()));
}

float Obstacle::getDistance(Position *p2) {
    return sqrt((x_p-p2->GetX())*(x_p-p2->GetX()) + (y_p-p2->GetY())*(y_p-p2->GetY()));
}



Obstacle::~Obstacle() {
}

