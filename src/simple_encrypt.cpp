/**************************************************************************************************
* Copyright (c) 2017 Anyongzhi. All rights reserved.
* File Name   : simple_encrypt.cpp
* Brief       :
* Key Words   :
* File Ext    : h
* Purpose     :
* Author      : ANYZ
* Create Date : 2016/10/27 11:10:37
* MODIFY DATE : 2016/10/27 11:10:37
**************************************************************************************************/
#include "simple_encrypt.h"
#include <fstream>

#include <string.h>

#define     XSTD_ENCRYPT_READ_MAX_SIZE   1024
#define     XSTD_ENCRYPT_MD5_SIZE        16
#define     XSTD_ENCRYPT_MD5_STR_LEN     (XSTD_ENCRYPT_MD5_SIZE * 2)

simple_encrypt::simple_encrypt(const char* s) {
    inputstr_.assign(s);
}

simple_encrypt::~simple_encrypt() {
    
}
void simple_encrypt::reset(std::string s) {
    inputstr_.assign(s);
}
/**
 * @Brief
 * @Method   md5
 * @DateTime 2016-10-27T10:28:52+0800
 * @Modify   2016-10-27T10:28:52+0800
 * @Author   Anyz
 * @Keyword
 * @param    urlstr [description]
 * @param    path [description]
 * @return   [description]
 */
std::string simple_encrypt::md5() {
    if (inputstr_.empty()) {
        return fileMd5();
    }
    MD5_CTX c;
    MD5_Init(&c);

    unsigned char md5val[256];
    MD5((const unsigned char*)inputstr_.c_str(), inputstr_.size(), md5val);

    char buf[65] = { 0 };
    char tmp[3] = { 0 };
    for (int i = 0; i < XSTD_ENCRYPT_MD5_STR_LEN; i++) {
        sprintf(tmp, "%02x", md5val[i]);
        strcat(buf, tmp);
    }
    buf[32] = '\0';
    std::string result(buf);
    printf("md5 of %s is %s\n", inputstr_.c_str(), result.c_str());

    return result;
}
/**
 * @Brief
 * @Method   sha256
 * @DateTime 2016-10-27T10:28:52+0800
 * @Modify   2016-10-27T10:28:52+0800
 * @Author   Anyz
 * @Keyword
 * @param    urlstr [description]
 * @param    path [description]
 * @return   [description]
 */
std::string simple_encrypt::sha256() {
    unsigned char shaStr[33] = { 0 };
    SHA256((const unsigned char *)inputstr_.c_str(), inputstr_.size(), shaStr);

    char buf[65] = { 0 };
    char tmp[3] = { 0 };
    for (int i = 0; i < XSTD_ENCRYPT_MD5_STR_LEN; i++) {
        sprintf(tmp, "%02x", shaStr[i]);
        strcat(buf, tmp);
    }
    buf[32] = '\0';

    std::string result(buf);
    printf("sha256 of %s is %s\n", inputstr_.c_str(), result.c_str());

    return result;
}
/**
 * @Brief    get local file size
 * @Method   localFile
 * @DateTime 2018-06-25T09:44:30+0800
 * @Modify   2018-06-25T09:44:30+0800
 * @Author   Anyz
 * @Keyword
 * @param    filename [description]
 * @return   file size
 */
long simple_encrypt::localFile(const char* filename) {
    if (!fileExists(filename)) {
        printf("file path invalid.\n");
        return -1;
    }
    filename_ = filename;
    FILE* fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fclose(fp);
    return fileSize;
}
/**
 * @Brief    file exists or not
 * @Method   fileExists
 * @DateTime 2018-06-25T09:44:34+0800
 * @Modify   2018-06-25T09:44:34+0800
 * @Author   Anyz
 * @Keyword
 * @param    filename [description]
 * @return   true if file exists
 */
bool simple_encrypt::fileExists(const char* filename) {
    std::string filePath(filename);
    std::ifstream fs;
    fs.open(filePath.c_str(), std::ios::in);
    if (!fs) {
        return false;
    } else {
        fs.close();
        return true;
    }
}
/**
 * @Brief    file md5 string
 * @Method   fileMd5
 * @DateTime 2018-06-25T09:44:37+0800
 * @Modify   2018-06-25T09:44:37+0800
 * @Author   Anyz
 * @Keyword
 * @return   [description]
 */
std::string simple_encrypt::fileMd5() {
    FILE*   fp;
    int     ret = 0;
    unsigned char   data[XSTD_ENCRYPT_READ_MAX_SIZE];
    unsigned char   md5_value[XSTD_ENCRYPT_MD5_SIZE];
    char            md5str[XSTD_ENCRYPT_MD5_STR_LEN + 1];
    MD5_CTX         md5;

    if ((fp = fopen(filename_.c_str(), "rb")) < 0) {
        printf("open failed\n");
        return "";
    }
    MD5_Init(&md5);

    while (!feof(fp)) {
        ret = fread(data, 1, XSTD_ENCRYPT_READ_MAX_SIZE, fp);
        if (ret == -1) {
            printf("read failed\n");
            fclose(fp);
            return "";
        }
        MD5_Update(&md5, data, ret);
        if (ret == 0 || ret < XSTD_ENCRYPT_READ_MAX_SIZE) {
            break;
        }
        //fclose(fp);
    }
    MD5_Final((unsigned char *)&md5_value, &md5);
    for (int i = 0; i < XSTD_ENCRYPT_MD5_SIZE; i++) {
        snprintf(md5str + i * 2, 2 + 1, "%02x", md5_value[i]);
    }
    md5str[XSTD_ENCRYPT_MD5_STR_LEN] = '\0';
    
    fclose(fp);
    std::string s(md5str);
    return s;
}
