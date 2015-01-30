/* 
 * File:   socketUtilClass.cpp
 * Author: root
 * 
 * Created on Streda, 2015, január 28, 10:26
 */

#include "socketUtilClass.h"

socketUtilClass::socketUtilClass() {
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

const char * socketUtilClass::parseClassTypeFromJson(const char *json) {
    rapidjson::Document document;
    document.Parse<0>(json);
    
    std::string ctype = document["CLASSTYPE"].GetString();
    
    return ctype.c_str();
}

socketUtilClass::~socketUtilClass() {
}

