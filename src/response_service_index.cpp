/**
 * @File     response_service_index.cpp
 * @Brief    
 * @DateTime 2018-07-23T12:05:23+0800
 * @Modify   2018-07-23T12:05:23+0800
 * @Author   Anyz
 */

#include "json/json.h"
#include "simple_encrypt.h"
//#include "time_utils.h"
#include "http_server.h"
#include <memory.h>

#include <string>

void append_item(std::string& s, const char* uriPrefix, const char* uriSuffix) {
    s.append("===>> <a href=http://");
    s.append(uriPrefix);
    s.append(uriSuffix);
    s.append("<br></a>");
}

/**
 * @Method   response_index
 * @Brief
 * @param    hs                       [description]
 * @param    req                      [description]
 * @param    url                      [description]
 * @Author   Anyz
 * @DateTime 2018-04-17T14:32:25+0800
 * @Modyfiy  2018-04-17T14:32:25+0800
 */
void response_index(http_server* hs, EvHttpRequest* req, const char* url) {
    std::string hostip = hs->hostip();
    int port = hs->port();
    char uriPrefix[32];
    memset(uriPrefix, 0, sizeof(uriPrefix));
    sprintf(uriPrefix, "%s:%d", hostip.c_str(), port);
    std::string s;
    s.append("<head><h2><b>Welcome to Simple Chain<b></h1></head><br>");
    s.append("<hr style='border:3 solid ##ff0033' width='100%'' SIZE=3>");
    s.append("<body>");
    s.append("<h3>");

    append_item(s, uriPrefix, "/help>Help");
    append_item(s, uriPrefix, "/version>Version");
    append_item(s, uriPrefix, "/init>Initialized Block");
    append_item(s, uriPrefix, "/haveatry>Have a Try");


    s.append("</h3></body>");

    hs->reply(req, 200, "OK", s.c_str());
}
