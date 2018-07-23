/**
 * @File     response_service_version.cpp
 * @Brief    
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */

#include "json/json.h"
#include "simple_encrypt.h"
//#include "time_utils.h"
#include "http_server.h"

#include <string>
/**
 * @Method   response_version
 * @Brief
 * @param    hs                       [description]
 * @param    req                      [description]
 * @param    url                      [description]
 * @Author   Anyz
 * @DateTime 2018-04-17T14:32:25+0800
 * @Modyfiy  2018-04-17T14:32:25+0800
 */
void response_version(http_server* hs, EvHttpRequest* req, const char* url) {
    Json::Value jsonObject;
    jsonObject["Name"]        = "Simple Chain";
    jsonObject["ID"]          = "9527-00001";
    jsonObject["Version"]     = "sc-v0.0.0.1";
    Json::StyledWriter sw;
    std::string s = sw.write(jsonObject);
    hs->reply(req, 200, "OK", s.c_str());
}
