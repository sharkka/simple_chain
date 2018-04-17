/**
 * @File     
 * @Brief    
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */
#ifndef __RESPONSE_SERVICES_H_
#define __RESPONSE_SERVICES_H_

#include "http_server.h"

extern void response_version(http_server* hs, EvHttpRequest* req, const char* url);
extern void response_init(http_server* hs, EvHttpRequest* req, const char* url);


#endif

