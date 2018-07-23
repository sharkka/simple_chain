/**
 * @File     response_service_haveatry.cpp
 * @Brief    
 * @DateTime 2018-07-23T14:03:23+0800
 * @Modify   2018-07-23T14:03:23+0800
 * @Author   Anyz
 */

#include "json/json.h"
#include "simple_encrypt.h"
//#include "time_utils.h"
#include "http_server.h"
#include <memory.h>

#include <string>
/**
 * @Method   response_haveatry
 * @Brief
 * @param    hs                       [description]
 * @param    req                      [description]
 * @param    url                      [description]
 * @Author   Anyz
 * @DateTime 2018/7/23 14:04:01
 * @Modyfiy  2018/7/23 14:04:06
 */
void response_haveatry(http_server* hs, EvHttpRequest* req, const char* url) {
    std::string s;
    s.append("<head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>");
    s.append("<h2><b>Welcome to Simple Chain Help Page<b></h1></head><br>");
    s.append("<hr style='border:1 solid ##ff0033' width='100%' SIZE=3>");
    s.append("<body>");
    s.append("<h3><font face='Courier New'>");
    s.append("<form >");
    s.append("Account:<br>");
    s.append("<input type='text' name='Account' value='62220505'>");
    s.append("<br>");
    s.append("Cash:<br>");
    s.append("<input type='text' onkeyup=\"this.value=this.value.replace(/[^0-9-]+/,'');\" />");
    s.append("<br><br>");
    s.append("<input type='submit' value='Submit'>");
    s.append("</form> ");

    s.append("<br>");

    s.append("<face></h3></body>");

    hs->reply(req, 200, "OK", s.c_str());
}
