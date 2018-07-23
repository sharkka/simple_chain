/**
 * @File     response_service_chaining.cpp
 * @Brief    
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */
#include <memory.h>
#include "json/json.h"
#include "simple_encrypt.h"
#include "http_server.h"
#include "simple_chain_service.h"
#include "time_utils.h"
#include "common_utils.h"

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
void response_chaining(http_server* hs, EvHttpRequest* req, const char* url) {
    simple_chain_service* scs = reinterpret_cast<simple_chain_service*>(hs->userHandle);
    std::string s = "<html><font size=2 face='Courier New' italic bold>";
    s.append("<head><h2><b>Welcome to Simple Chain Commit Your Trade<b></h1></head><br>");
    common_utils::toHomePage(hs, s);

    s.append("<hr style='border:3 solid ##ff0033' width='100%' SIZE=3>");
    s.append("<body onload='window.scrollTo(0,document.body.scrollHeight);'>");
    Json::Value jsonObject;
    std::string tailItem = scs->newestTradeItem();
    char indexStr[28];
    memset(indexStr, 0, sizeof(indexStr));
    sprintf(indexStr, "%03ld", scs->index());
    jsonObject["Name"]         = "Naraka";
    jsonObject["Index"]        = indexStr;
    jsonObject["Datetime"]     = time_utils::currentTime();
    simple_encrypt se(tailItem.c_str());
    std::string chash = se.sha256();
    jsonObject["Hash"]         = chash;
    Json::StyledWriter sw;
    std::string sitem = sw.write(jsonObject);
    scs->addTradeItem(sitem);

    auto ssl = scs->tradeList();
    for (auto k : ssl) {
        s.append(k);
        s.append("<br>");
    }
    scs->incIndex();
    s.append("</body>");
    s.append("</font></html>");
    

    hs->reply(req, 200, "OK", s.c_str());
}
