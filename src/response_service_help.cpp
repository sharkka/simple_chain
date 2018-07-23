/**
 * @File     response_service_help.cpp
 * @Brief    
 * @DateTime 2018-07-23T14:03:23+0800
 * @Modify   2018-07-23T14:03:23+0800
 * @Author   Anyz
 */

#include "json/json.h"
#include "simple_encrypt.h"
#include "http_server.h"
#include "common_utils.h"

#include <memory.h>
#include <string>

/**
 * @Method   response_help
 * @Brief
 * @param    hs                       [description]
 * @param    req                      [description]
 * @param    url                      [description]
 * @Author   Anyz
 * @DateTime 2018/7/23 14:04:01
 * @Modyfiy  2018/7/23 14:04:06
 */
void response_help(http_server* hs, EvHttpRequest* req, const char* url) {
    std::string s;
    s.append("<head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>");
    s.append("<h2><b>Welcome to Simple Chain Help Page<b></h1></head><br>");
    common_utils::toHomePage(hs, s);
    s.append("<hr style='border:1 solid ##ff0033' width='100%' SIZE=3>");
    s.append("<body>");
    s.append("<h3><font face='Courier New'>");
    s.append("         God, give us grace to accept with serenity<br>");
    s.append("         the things that cannot be changed,<br>");
    s.append("         courage to change the things<br>");
    s.append("         which should be changed,<br>");
    s.append("         and the wisdom to distinguish<br>");
    s.append("         the one from the other. <br>");
    s.append("         Living one day at a time,<br>");
    s.append("         njoying one moment at a time,<br>");
    s.append("         Accepting hardship as a pathway to peace,<br>");
    s.append("         Taking, as Jesus did,<br>");
    s.append("         This sinful world as it is,<br>");
    s.append("         Not as I would have it,<br>");
    s.append("         Trusting that You will make all things right,<br>");
    s.append("         f I surrender to Your will,<br>");
    s.append("         So that I may be reasonably happy in this life,<br>");
    s.append("         And supremely happy with You forever in the next.<br>");
    s.append("         Amen.<br>");

    s.append("<br>");

    s.append("<face></h3></body>");

    hs->reply(req, 200, "OK", s.c_str());
}
