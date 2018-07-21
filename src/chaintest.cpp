
#include "http_server.h"
#include "json/json.h"

static void response_version(http_server* hs, EvHttpRequest* req, const char* url) {
    Json::Value jsonObject;
    jsonObject["Name"] = "Simple Chain";
    jsonObject["ID"]   = "9527-00001";
    jsonObject["Version"]     = "sc-v0.0.0.1";
    Json::StyledWriter sw;
    std::string s = sw.write(jsonObject);
    hs->reply(req, 200, "OK", s.c_str());
}
static void response_type(http_server* hs, EvHttpRequest* req, const char* url) {
    const char* jsonstr = "{\"name\": \"TYPE TEST\", \"id\", \"9527-11111\"}";
    hs->reply(req, 200, "OK", jsonstr);
}
static void response_id(http_server* hs, EvHttpRequest* req, const char* url) {
    const char* jsonstr = "{\"name\": \"ID TEST\", \"id\", \"9527-22222\"}";
    hs->reply(req, 200, "OK", jsonstr);
}
static void response_status(http_server* hs, EvHttpRequest* req, const char* url) {
    const char* jsonstr = "{\"name\": \"STATUS TEST\", \"id\", \"9527-33333\"}";
    hs->reply(req, 200, "OK", jsonstr);
}
static void response_speed(http_server* hs, EvHttpRequest* req, const char* url) {
    const char* jsonstr = "{\"name\": \"SPEED TEST\", \"id\", \"9527-55555\"}";
    hs->reply(req, 200, "OK", jsonstr);
}

static void response_error(http_server* hs, EvHttpRequest* req, const char* url) {
    const char* jsonstr
        = "<html><h><font size=8 color=\"blue\" face=\"Comic Sans MS\" italic bold>ERROR REQUEST TEST ......</font></h></html>";
    hs->reply(req, 407, "Request not allowed", jsonstr);
}

static void http_server_test() {
    const char* url_01 = "/version";
    const char* url_02 = "/type";
    const char* url_03 = "/id";
    const char* url_04 = "/status";
    const char* url_05 = "/speed";
    const char* url_06 = "/error";
    http_server hs(9090);
    hs.push(url_01, response_version);
    hs.push(url_02, response_type);
    hs.push(url_03, response_id);
    hs.push(url_04, response_status);
    hs.push(url_05, response_speed);
    hs.push(url_06, response_error);

    hs.start();
}

int main() {
    http_server_test();
    return 0;
}
