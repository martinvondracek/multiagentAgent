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
    
    static std::string createQuit(int idAgenta);
    static std::string createInvalidKoorSur(int idAgenta);
    static std::string createInAccesibleKoorSur(int idAgenta);
    static std::string createNewIdPrekazky();
    
    static int parseAgentIdFromJson(const char *json);
    static int parseAgentIdSpusteniaFromJson(const char *json);
    static int parseIdSpusteniaFromJson(const char *json);
    static int parseNewIdPrekazkyFromJson(const char *json);
    static std::string parseClassTypeFromJson(const char *json);
private:

};

#endif	/* SOCKETUTILCLASS_H */

