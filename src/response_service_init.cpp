/**
 * @File     response_service_init.cpp
 * @Brief    
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */

#include "json/json.h"
#include "simple_encrypt.h"
#include "time_utils.h"
#include "http_server.h"
/**
 * @Method
 * @Brief
 * @param    hs                       [description]
 * @param    req                      [description]
 * @param    url                      [description]
 * @Author   Anyz
 * @DateTime 2018-04-17T14:35:36+0800
 * @Modyfiy  2018-04-17T14:35:36+0800
 */
void response_init(http_server* hs, EvHttpRequest* req, const char* url) {
    std::string s = "<html><font size=2 face=\"Courier New\" italic bold>";
    Json::Value jsonObject;
    std::string name = "Initialization Block";
    jsonObject["Name"]         = name;
    jsonObject["ID"]           = "0000-0000-0000-0000-0001";
    jsonObject["Index"]        = "1";
    jsonObject["Datetime"]     = time_utils::currentTime();
    
    simple_encrypt se(name.c_str());
    std::string chash = se.sha256();
    jsonObject["hash"]         = chash;
    Json::StyledWriter sw;
    std::string s1 = sw.write(jsonObject);
    s1.append("<br>");
    jsonObject["Name"]         = "Sequence Block";
    jsonObject["ID"]           = "0000-0000-0000-0000-0002";
    jsonObject["Index"]        = "2";
    jsonObject["Datetime"]     = time_utils::currentTime();
    se.reset(chash);
    chash = se.sha256();
    jsonObject["hash"]         = chash;
    std::string s2 = sw.write(jsonObject);
    s.append(s1);
    s.append(s2);
    s.append("</font></html>");

    hs->reply(req, 200, "OK", s.c_str());
}
