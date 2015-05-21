/* 
 * File:   socketUtilClass.h
 * Author: root
 *
 * Created on Streda, 2015, január 28, 10:26
 */

#ifndef SOCKETUTILCLASS_H
#define	SOCKETUTILCLASS_H

#include <rapidjson/document.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <iostream>

class SocketUtil {
public:
    SocketUtil();
    virtual ~SocketUtil();
    
    static std::string createQuit(int idAgenta); //crate json that this agent quits
    static std::string createInvalidCoorPosition(int idAgenta); // creates json that coor position is invalid
    static std::string createInAccesibleCoorPosition(int idAgenta); // creates json that coor position is inaccesible
    static std::string createNewIdOfObstacle(); //creates json that agent wants new id of obstacle
    
    static int parseAgentIdFromJson(const char *json);
    static int parseAgentIdMappingFromJson(const char *json);
    static int parseIdMappingFromJson(const char *json);
    static int parseNewIdObstacleFromJson(const char *json);
    static std::string parseClassTypeFromJson(const char *json);
private:

};

#endif	/* SOCKETUTILCLASS_H */

