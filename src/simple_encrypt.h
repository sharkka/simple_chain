/**************************************************************************************************
* Copyright (c) 2017 Anyongzhi. All rights reserved.
* File Name   : simple_encrypt.h
* Brief       :
* Key Words   :
* File Ext    : h
* Purpose     :
* Author      : ANYZ
* Create Date : 2016/10/27 11:10:37
* MODIFY DATE : 2016/10/27 11:10:37
**************************************************************************************************/
#ifndef __SIMPLE_ENCRYPT_H_
#define __SIMPLE_ENCRYPT_H

#include <string>
#include "openssl/md5.h"
#include "openssl/sha.h"

/**
 * Class Name  : simple_encrypt
 * Brief       : 
 * Key Words   :
 * Purpose     : 
 * Author      : ANYZ
 * Create Date : 2016/10/27 11:10:37
 * Modify Date : 2016/10/27 11:10:37 
 */
class simple_encrypt {
public:
    simple_encrypt() {}
    explicit simple_encrypt(const char* s);
    ~simple_encrypt();
    long           localFile(const char* filename);
    std::string    md5();
    std::string    fileMd5();
    std::string    sha256();
    void           reset(std::string s);
    bool           fileExists(const char* filename);

private:
    std::string inputstr_;
    std::string filename_;
};

#endif
