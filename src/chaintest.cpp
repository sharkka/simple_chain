/**
 * @File     chaintest.cpp
 * @Brief    
 * @Author   Anyz
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 */
#include "simple_chain_service.h"
#include "response_services.h"


struct resp_pack_t {
    const char*      url;
    ResponseCallback resp_cb;

    resp_pack_t(const char* url, ResponseCallback cb) 
    : url(url), resp_cb(cb) {
    }
};

/**
 * @Method   http_server_test
 * @Brief    
 * @Author   Anyz
 * @DateTime 2018-04-17T14:31:14+0800
 * @Modyfiy  2018-04-17T14:31:14+0800
 * @Keyword
 */
static void http_server_test() {
    resp_pack_t resp[] = {
        {"/version", response_version},
        {"/init", response_init},
        {"/index", response_index},
        {"/help", response_help},
        {"/haveatry", response_haveatry},
        {"/chaining", response_chaining}
    };

    simple_chain_service scs(9090);
    for (unsigned int i = 0; i < sizeof(resp) / sizeof(resp_pack_t); ++i) {
        scs.addService(resp[i].url, resp[i].resp_cb);
    }

    scs.start();
}

int main() {
    http_server_test();
    return 0;
}
