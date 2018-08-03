/**
 * @File     http_server.h
 * @Brief    simple http server via libevent
 * @DateTime 2018-07-20T14:32:12+0800
 * @Modify   2018-07-20T14:32:12+0800
 * @Author   Anyz
 */
#ifndef __HTTP_SERVER_H_
#define __HTTP_SERVER_H_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "event2/event.h"
#include "event2/http.h"
#include "event2/buffer.h"
#include "event2/util.h"
#include "event2/keyvalq_struct.h"

#include <string>
#include <list>
#include <map>

#define XSTD_UNUSED(x) ((void)(x))


class http_server;

using StlString         = std::string;
using StlStringList     = std::list<std::string>;
using StlStringListIter = std::list<std::string>::iterator;
using EvBase            = struct event_base;
using EvHttpHandle      = struct evhttp;
using EvHttpBoundSock   = struct evhttp_bound_socket;
using EvHttpRequest     = struct evhttp_request;

typedef void(*ResponseCallback)(http_server* handle, EvHttpRequest* req, const char* url);
typedef void(*SendResponseCallback)(EvHttpRequest* req, void* arg);

typedef struct _RespCallbackBroker {
    ResponseCallback     respCb;
    SendResponseCallback sendRespCb;
} RespCallbackBroker;
using RespHandlers      = std::map<std::string, RespCallbackBroker>;
/**
 * @Class    http_server
 * @Brief    simple http server
 * @Author   Anyz
 * @DateTime 2018-07-19T18:31:32+0800
 * @Modify   2018-07-19T18:31:32+0800
 */
class http_server {
public:
    http_server();
    explicit http_server(int port);
    ~http_server();

    int              listenPort(int port);
    std::string      hostip() const;
    int              port() const;
    int              push(const char* url, ResponseCallback servCallback);
    int              pushUri(const char* url);
    int              popUri(const char* url);
    StlString        requestHeader(EvHttpRequest* req, const char* url, const char* key);
    StlString        requestData(EvHttpRequest* req, const char* url);
    int              pushResponseHeader(EvHttpRequest* req, const char* url, const char* key, const char* value);
    int              setResponseData(EvHttpRequest* req, const char* data, struct evbuffer*& buff);
    int              registerResponseCallback(const char* url, ResponseCallback servCallback);
    int              start();
    int              stop();
    void             cleanup();
    int              reply(const EvHttpRequest* req, int code, const char* reason, const char* content);
    int              send(const EvHttpRequest* req, int code, const char* reason, char* buffdata, int len);

    RespHandlers     respCallbacks;
    void*            userHandle;

private:
    const char*      commandType(EvHttpRequest* req) const;
    std::string      localAddress();

    EvBase*          base_;
    EvHttpHandle*    http_;
    EvHttpBoundSock* boundfd_;
    int              port_;
    char             localaddr_[20];
    StlStringList    urlList_;
    char             uriRoot_[512];
    static void      responseSender(struct evhttp_request *req, void *arg);
};

#endif
