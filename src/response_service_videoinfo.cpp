/**
 * @File     response_service_videoinfo.cpp
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
 * @Method   response_videoinfo
 * @Brief
 * @param    hs                       [description]
 * @param    req                      [description]
 * @param    url                      [description]
 * @Author   Anyz
 * @DateTime 2018-04-17T14:32:25+0800
 * @Modyfiy  2018-04-17T14:32:25+0800
 */
void response_videoinfo(http_server* hs, EvHttpRequest* req, const char* url) {
    //std::string s = "<html><font size=2 face='Courier New' italic bold>";
    //s.append("<head><h2><b>Welcome to GA/T 1400 Test Page<b></h1></head><br>");
    //common_utils::toHomePage(hs, s);
    //s.append("<hr style='border:3 solid ##ff0033' width='100%' SIZE=3><br>");

    std::string s;
    //std::string data = hs->requestData(req, url);
    //printf("%s\n", data.c_str());
    std::string data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><complexType name=\"ColorArea\"><sequence><element name=\"AreaPosX\" type=\"int\" /><element name=\"AreaPosY\" type=\"int\" /></sequence></complexType>";
    //std::string data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><complexType name=\"ColorArea\">ccccccc</complexType>";
    s.append(data);
    printf("%s\n", data.c_str());
    //Json::Value jsonObject;
    //jsonObject["Name"]        = "video information";
    //jsonObject["ID"]          = "003";
    //jsonObject["Version"]     = "sc-v0.0.0.9";
    //Json::StyledWriter sw;
    //std::string sj = sw.write(jsonObject);
    //s.append(sj);
    hs->reply(req, 200, "OK", s.c_str());
}
