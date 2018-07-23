/**
 * @File     common_utils.h
 * @Brief    
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */
#ifndef __COMMON_UTILS_H_
#define __COMMON_UTILS_H_

#include <stdlib.h>
#include <memory.h>
#include <string>
#include "http_server.h"

/**
 * @Class    common_utils
 * @Brief    
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */
class common_utils {
public:
    static void toHomePage(http_server* hs, std::string& s) {
        s.append("<a href=http://");
        std::string hostip = hs->hostip();
        int port = hs->port();
        char idxPage[256];
        memset(idxPage, 0, sizeof(idxPage));
        sprintf(idxPage, "%s:%d/index", hostip.c_str(), port);
        s.append(idxPage);
        s.append(">Home</a><br>");
    }
};

#endif
