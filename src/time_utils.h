/**
 * @File     time_utils.h
 * @Brief    
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */
#ifndef __TIME_UTILS_H_
#define __TIME_UTILS_H_

#include <stdlib.h>
/**
 * @Class    time_utils
 * @Brief    
 * @DateTime 2018-07-21T23:18:23+0800
 * @Modify   2018-07-21T23:18:23+0800
 * @Author   Anyz
 */
class time_utils {
public:
    static std::string currentTime() {
        time_t tt;
        time(&tt);
        char s[64];
        strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", localtime(&tt));
        return s;
    }
}

#endif
