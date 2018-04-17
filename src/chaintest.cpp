/**
 * @File     chaintest.cpp
 * @Brief    
 * @Author   Anyz
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 */
#include "simple_chain_service.h"
#include "response_services.h"
/**
 * @Method   http_server_test
 * @Brief    
 * @Author   Anyz
 * @DateTime 2018-04-17T14:31:14+0800
 * @Modyfiy  2018-04-17T14:31:14+0800
 * @Keyword
 */
static void http_server_test() {
    const char* url_01 = "/version";
    const char* url_02 = "/init";
    const char* url_03 = "/id";
    const char* url_04 = "/status";
    const char* url_05 = "/speed";
    const char* url_06 = "/error";

    simple_chain_service scs;
    scs.addService(url_01, response_version);
    scs.addService(url_02, reponse_init);
    hs.start();
}

int main() {
    http_server_test();
    return 0;
}
