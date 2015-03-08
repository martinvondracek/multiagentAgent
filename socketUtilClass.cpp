/* 
 * File:   socketUtilClass.cpp
 * Author: root
 * 
 * Created on Streda, 2015, január 28, 10:26
 */

#include "socketUtilClass.h"

socketUtilClass::socketUtilClass() {
}

const char * socketUtilClass::createQuit(int idAgenta) {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"QUIT\"");
    
    json.append(",\n\"ID\" : ");
    json.append(std::to_string(idAgenta));
    
    json.append("\n}\n");
        
    return json.c_str();
}

const char * socketUtilClass::createNewIdPrekazky() {
    std::string json = "{\n";
    json.append("\"CLASSTYPE\" : \"NEW_ID_PREKAZKY\"");
    
    json.append("\n}\n");
        
    return json.c_str();
}

int socketUtilClass::parseAgentIdFromJson(const char *json) {
    int id;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    if (ctype.compare("AGENTID") == 0) {
        id = document["ID"].GetInt();
        return id;
    } else {
        return -1;
    }
}

int socketUtilClass::parseAgentIdSpusteniaFromJson(const char *json) {
    int id;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    if (ctype.compare("AGENTID") == 0) {
        id = document["ID_SPUSTENIA"].GetInt();
        return id;
    } else {
        return -1;
    }
}

int socketUtilClass::parseIdSpusteniaFromJson(const char *json) {
    int id;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    if (ctype.compare("ID_SPUSTENIA") == 0) {
        id = document["ID_SPUSTENIA"].GetInt();
        return id;
    } else {
        return -1;
    }
}

int socketUtilClass::parseNewIdPrekazkyFromJson(const char *json) {
    int id;
    
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    if (ctype.compare("NEW_ID_PREKAZKY") == 0) {
        id = document["ID_PREKAZKY"].GetInt();
        return id;
    } else {
        return -1;
    }
}

std::string socketUtilClass::parseClassTypeFromJson(const char *json) {
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    
    return ctype;
}

socketUtilClass::~socketUtilClass() {
}

