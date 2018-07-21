
#include "http_server.h"
#include "json/json.h"
#include "simple_encrypt.h"

std::string currentTime() {
    time_t tt;
    time(&tt);
    char s[64];
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", localtime(&tt));
    return s;
}

static void response_version(http_server* hs, EvHttpRequest* req, const char* url) {
    Json::Value jsonObject;
    jsonObject["Name"]        = "Simple Chain";
    jsonObject["ID"]          = "9527-00001";
    jsonObject["Version"]     = "sc-v0.0.0.1";
    Json::StyledWriter sw;
    std::string s = sw.write(jsonObject);
    hs->reply(req, 200, "OK", s.c_str());
}

static void response_init(http_server* hs, EvHttpRequest* req, const char* url) {
    std::string s = "<html><font size=2 face=\"Courier New\" italic bold>";
    Json::Value jsonObject;
    std::string name = "Initialization Block";
    jsonObject["Name"]         = name;
    jsonObject["ID"]           = "0000-0000-0000-0000-0001";
    jsonObject["Index"]        = "1";
    jsonObject["Datetime"]     = currentTime();
    
    simple_encrypt se(name.c_str());
    std::string chash = se.sha256();
    jsonObject["hash"]         = chash;
    Json::StyledWriter sw;
    std::string s1 = sw.write(jsonObject);
    s1.append("<br>");
    jsonObject["Name"]         = "Sequence Block";
    jsonObject["ID"]           = "0000-0000-0000-0000-0002";
    jsonObject["Index"]        = "2";
    jsonObject["Datetime"]     = currentTime();
    se.reset(chash);
    chash = se.sha256();
    jsonObject["hash"]         = chash;
    std::string s2 = sw.write(jsonObject);
    s.append(s1);
    s.append(s2);
    s.append("</font></html>");

    hs->reply(req, 200, "OK", s.c_str());
}


static void http_server_test() {
    const char* url_01 = "/version";
    const char* url_02 = "/init";
    const char* url_03 = "/id";
    const char* url_04 = "/status";
    const char* url_05 = "/speed";
    const char* url_06 = "/error";
    http_server hs(9090);
    hs.push(url_01, response_version);
    hs.push(url_02, response_init);
    //hs.push(url_03, response_id);
    //hs.push(url_04, response_status);
    //hs.push(url_05, response_speed);
    //hs.push(url_06, response_error);

    hs.start();
}

int main() {
    http_server_test();
    return 0;
}
