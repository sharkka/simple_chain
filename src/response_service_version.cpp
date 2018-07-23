/**
 * @File     response_service_version.cpp
 * @Brief    
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */

#include "json/json.h"
#include "simple_encrypt.h"
#include "http_server.h"
#include "simple_chain_service.h"
#include "common_utils.h"

#include <string>
#include <memory.h>

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
    std::string s = "<html><font size=2 face='Courier New' italic bold>";
    s.append("<head><h2><b>Welcome to Simple Chain Version<b></h1></head><br>");
    common_utils::toHomePage(hs, s);
    s.append("<hr style='border:3 solid ##ff0033' width='100%' SIZE=3>");

    Json::Value jsonObject;
    jsonObject["Name"]        = "Simple Chain";
    jsonObject["ID"]          = "9527-00001";
    jsonObject["Version"]     = "sc-v0.0.0.1";
    Json::StyledWriter sw;
    std::string sj = sw.write(jsonObject);
    s.append(sj);
    hs->reply(req, 200, "OK", s.c_str());
}
