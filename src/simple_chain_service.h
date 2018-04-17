/**
 * @File     simple_chain_service
 * @Brief    simple chain service
 * @DateTime 2018-07-21T17:28:23+0800
 * @Modify   2018-07-21T17:28:23+0800
 * @Author   Anyz
 * @Keyword
 */
#ifndef __SIMPLE_CHAIN_SERVICE_H_
#define __SIMPLE_CHAIN_SERVICE_H_

#include "http_server.h"


/**
 * @Brief    trade process
 * @Class    simple_chian_service
 * @DateTime 2018-07-21T23:17:23+0800
 * @Modify   2018-07-21T23:17:23+0800
 * @Author   Anyz
 * @Keyword
 */
class simple_chain_service {
public:
    simple_chain_service();
    explicit simple_chain_service(int port);
    ~simple_chain_service();

    void listenPort(int port);
    void addService(const char* url, ResponseCallback servCallback);
    int  start();

private:
    http_server httpServer_;
    int         port_;
};






#endif

