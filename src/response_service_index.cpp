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
    s.append("<head><h2><b>Welcome to simple chain<b></h1></head><br>");
    s.append("<body>");
    s.append("<h3>");
    s.append("===>> <a href=http://");
    s.append(uriPrefix);
    s.append("/version>version</a>");
    s.append("<br>");
    s.append("===>> <a href=http://");
    s.append(uriPrefix);
    s.append("/init>initialized block</a>");
    s.append("<br>");

    s.append("</h3></body>");

    hs->reply(req, 200, "OK", s.c_str());
}
