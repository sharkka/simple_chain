/**
 * @File     simple_chain_service.cpp
 * @Brief    simple chain service
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */

#include "simple_chain_service.h"
#include "response_services.h"

simple_chain_service::simple_chain_service() {
    port_ = 9090;
}

simple_chain_service::simple_chain_service(int port) {
    listenPort(port);
}

simple_chain_service::~simple_chain_service() {

}
/**
 * @Method   listenPort
 * @Brief
 * @param    port                     [description]
 * @Author   Anyz
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modyfiy  2018-07-21T23:18:23+0800
 */
void simple_chain_service::listenPort(int port) {
    port_ = port;
    httpServer_.listenPort(port);
}
/**
 * @Method   addService
 * @Brief
 * @param    url                      [description]
 * @param    servCallback             [description]
 * @Author   Anyz
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modyfiy  2018-07-21T23:18:23+0800
 * @Keyword
 */
void simple_chain_service::addService(const char* url, ResponseCallback servCallback) {
    httpServer_.push(url, servCallback);
}
/**
 * @Method   start
 * @Brief
 * @Author   Anyz
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modyfiy  2018-07-21T23:18:23+0800
 * @return   [description]
 */
int simple_chain_service::start() {
    httpServer_.start();
}
