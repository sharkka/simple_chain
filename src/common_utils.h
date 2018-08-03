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
#include <algorithm>

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
    /**
     * @Brief
     * @Method   toUpper
     * @DateTime 2018-06-26T15:56:23+0800
     * @Modify   2018-06-26T15:56:23+0800
     * @Author   Anyz
     * @Keyword
     * @param    s [description]
     * @return   [description]
     */
    static std::string& toUpper(std::string& s) {
        std::string& r = s;
        std::transform(r.begin(), r.end(), r.begin(), ::toupper);
        return r;
    }
    /**
     * @Brief
     * @Method   toLower
     * @DateTime 2018-06-26T15:56:29+0800
     * @Modify   2018-06-26T15:56:29+0800
     * @Author   Anyz
     * @Keyword
     * @param    s [description]
     * @return   [description]
     */
    static std::string& toLower(std::string& s) {
        std::string& r = s;
        std::transform(r.begin(), r.end(), r.begin(), ::tolower);
        return r;
    }

};

#endif
