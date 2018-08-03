/**
 * @File     http_server.cpp
 * @Brief    simple http server via libevent
 * @DateTime 2018-07-20T14:32:12+0800
 * @Modify   2018-07-20T14:32:12+0800
 * @Author   Anyz
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#ifndef S_ISDIR
#define S_ISDIR(x) (((x) & S_IFMT) == S_IFDIR)
#endif
#else
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <arpa/inet.h>
#endif
#include "http_server.h"

#if defined(_WIN32) || defined(_WIN64)
  #pragma comment(lib, "ws2_32.lib")
#else

#endif
/**
 * @Brief    constructor
 * @Method   http_server
 * @DateTime 2018-07-20T14:32:12+0800
 * @Modify   2018-07-20T14:32:12+0800
 * @Author   Anyz
 * @Keyword
 * @param    port [description]
 * @return   [description]
 */
http_server::http_server() {
    // default
    port_ = 8080;
    std::string ip = localAddress();
    if (ip.empty()) {
        printf("WARNING: get local ip address failed.\n");
    }
}
/**
 * @Brief    constructor with listening port
 * @Method   http_server
 * @DateTime 2018-07-20T14:32:12+0800
 * @Modify   2018-07-20T14:32:12+0800
 * @Author   Anyz
 * @Keyword
 * @param    port [description]
 * @return   [description]
 */
http_server::http_server(int port) {
    listenPort(port);
}
/**
 * @Brief    destructor
 * @Method   ~http_server
 * @DateTime 2018-07-20T14:32:12+0800
 * @Modify   2018-07-20T14:32:12+0800
 * @Author   Anyz
 * @Keyword
 * @param    port [description]
 * @return   [description]
 */
http_server::~http_server() {
    cleanup();
}
/**
 * @Brief    set http listening port
 * @Method   listenPort
 * @DateTime 2018-07-20T14:32:12+0800
 * @Modify   2018-07-20T14:32:12+0800
 * @Author   Anyz
 * @Keyword
 * @param    port [description]
 * @return   [description]
 */
int http_server::listenPort(int port) {
    if (port > 1024)
        port_ = port;
    else {
        printf("port is not allowed range from 1~1024");
        return -1;
    }
    return 0;
}
/**
 * @Brief    push Uri
 * @Method   pushRequest
 * @DateTime 2018-07-19T18:31:17+0800
 * @Modify   2018-07-19T18:31:17+0800
 * @Author   Anyz
 * @Keyword
 * @param    url [description]
 * @return   [description]
 */
int http_server::pushUri(const char* url) {
    urlList_.push_back(url);
    return 0;
}
/**
 * @Brief    push url & reponse callback function pair togetther to list
 * @Method   push
 * @DateTime 2018-07-20T17:33:23+0800
 * @Modify   2018-07-20T17:33:23+0800
 * @Author   Anyz
 * @Keyword
 * @param    url [description]
 * @param    servCallback [description]
 * @return   [description]
 */
int http_server::push(const char* url, ResponseCallback servCallback) {
    pushUri(url);
    registerResponseCallback(url, servCallback);
    return 0;
}

/**
 * @Brief
 * @Method   removeRequest
 * @DateTime 2018-07-19T18:31:20+0800
 * @Modify   2018-07-19T18:31:20+0800
 * @Author   Anyz
 * @Keyword
 * @param    url [description]
 * @return   [description]
 */
int http_server::popUri(const char* url) {
    // not thread safe
    for (StlStringListIter pos = urlList_.begin(); pos != urlList_.end(); ++pos) {
        if (0 == pos->compare(url)) {
            urlList_.erase(pos);
            return 0;
        }
    }
    return -1;
}
/**
 * @Brief    get request header by key
 * @Method   requestHeader
 * @DateTime 2018-07-19T18:31:23+0800
 * @Modify   2018-07-19T18:31:23+0800
 * @Author   Anyz
 * @Keyword
 * @param    url [description]
 * @param    key [description]
 * @return   [description]
 */
StlString http_server::requestHeader(EvHttpRequest* req, const char* url, const char* key) {
    struct evkeyvalq *headers;
    struct evkeyval *header;
    headers = evhttp_request_get_input_headers(req);
    for (header = headers->tqh_first; header; header = header->next.tqe_next) {
        if (!memcmp(header->key, key, strlen(key))) {
            printf("  %s: %s\n", header->key, header->value);
            return header->value;
        }
    }
    return "";
}
/**
 * @Brief    get request data
 * @Method   requestData
 * @DateTime 2018-07-19T18:31:45+0800
 * @Modify   2018-07-19T18:31:45+0800
 * @Author   Anyz
 * @Keyword
 * @param    url [description]
 * @return   [description]
 */
StlString http_server::requestData(EvHttpRequest* req, const char* url) {
    struct evbuffer* evbuf = evhttp_request_get_input_buffer(req);
    StlString str;

    while (evbuffer_get_length(evbuf)) {
        int n;
        char buff[1024];
        n = evbuffer_remove(evbuf, buff, sizeof(buff));
        if (n > 0) {
            str.append(buff);
        }
    }
    return str;
}
/**
 * @Brief    push response header by key-value pattern
 * @Method   pushResponseHeader
 * @DateTime 2018-07-19T18:31:43+0800
 * @Modify   2018-07-19T18:31:43+0800
 * @Author   Anyz
 * @Keyword
 * @param    url [description]
 * @param    key [description]
 * @param    value [description]
 * @return   [description]
 */
int http_server::pushResponseHeader(EvHttpRequest* req, const char* url, const char* key, const char* value) {
    //evhttp_add_header(evhttp_request_get_output_headers(req), "Server", commandType(req));
    evhttp_add_header(evhttp_request_get_output_headers(req), key, value);
    return 0;
}
/**
 * @Brief    x
 * @Method   setResponseData
 * @DateTime 2018-07-19T18:31:40+0800
 * @Modify   2018-07-19T18:31:40+0800
 * @Author   Anyz
 * @Keyword
 * @param    url [description]
 * @param    data [description]
 * @return   [description]
 */
int http_server::setResponseData(EvHttpRequest* req, const char* data, struct evbuffer*& buff) {
    if (!buff) {
        printf("buffer can not access\n");
        return -1;
    }
    evbuffer_add_printf(buff, "%s", data);
    return 0;
}
/**
 * @Brief    service response sender for all clients
 * @Method   responseSender
 * @DateTime 2018-07-20T14:32:43+0800
 * @Modify   2018-07-20T14:32:43+0800
 * @Author   Anyz
 * @Keyword
 * @param    req [description]
 * @param    arg [description]
 */
void http_server::responseSender(struct evhttp_request* req, void *arg) {
    http_server* hs = static_cast<http_server*>(arg);
    //struct evbuffer *evb = NULL;
    //const char *docroot = arg;
    const char *uri = evhttp_request_get_uri(req);
    struct evhttp_uri *decoded = NULL;
    //char *whole_path = NULL;

    //printf("Got a GET request for <%s>\n", uri);
    // Decode the URI
    decoded = evhttp_uri_parse(uri);
    if (!decoded) {
        printf("It's not a good URI. Sending BADREQUEST\n");
        evhttp_send_error(req, HTTP_BADREQUEST, 0);
        return;
    }
    ResponseCallback     respCb;
    auto cbp = hs->respCallbacks.find(uri);
    if (cbp != hs->respCallbacks.end()) {
        respCb = cbp->second.respCb;
    } else {
        printf("uri %s not found\n", uri);
        return;
    }
    respCb(hs, req, uri);
}
/**
 * @Brief
 * @Method   registerResponseCallback
 * @DateTime 2018-07-19T18:31:37+0800
 * @Modify   2018-07-19T18:31:37+0800
 * @Author   Anyz
 * @Keyword
 * @param    url [description]
 * @param    servCallback [description]
 * @return   [description]
 */
int http_server::registerResponseCallback(const char* url, ResponseCallback servCallback) {
    RespCallbackBroker rcp;
    rcp.respCb = servCallback;
    rcp.sendRespCb = responseSender;
    respCallbacks.insert(std::pair<std::string, RespCallbackBroker>(url, rcp));
    return 0;
}
/**
 * @Brief    start http server
 * @Method   start
 * @DateTime 2018-07-19T18:31:35+0800
 * @Modify   2018-07-19T18:31:35+0800
 * @Author   Anyz
 * @Keyword
 * @return   [description]
 */
int http_server::start() {
#if defined(_WIN32) || defined(_WIN64)
    WSADATA WSAData;
    WSAStartup(0x101, &WSAData);
#else
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        return 1;
#endif
    base_ = event_base_new();
    if (!base_) {
        fprintf(stderr, "Couldn't create an event_base: exiting\n");
        return 1;
    }
    http_ = evhttp_new(base_);
    if (!http_) {
        fprintf(stderr, "couldn't create evhttp. Exiting.\n");
        return 1;
    }
    SendResponseCallback sendRespCb;
    ResponseCallback     respCb;
    XSTD_UNUSED(respCb);
    for (StlStringListIter pos = urlList_.begin(); pos != urlList_.end(); ++pos) {
        auto cbp = respCallbacks.find(*pos);
        if (cbp != respCallbacks.end()) {
            sendRespCb = cbp->second.sendRespCb;
            respCb     = cbp->second.respCb;
        } else {
            printf("uri %s not found\n", pos->c_str());
            return -1;
        }
        evhttp_set_cb(http_, pos->c_str(), sendRespCb, (void*)this);
    }
    boundfd_ = evhttp_bind_socket_with_handle(http_, "0.0.0.0", port_);
    if (!boundfd_) {
        fprintf(stderr, "couldn't bind to port %d. Exiting.\n",
            (int)port_);
        return 1;
    }

    // Extract and display the address we're listening on.
    struct sockaddr_storage ss;
    evutil_socket_t fd;
    ev_socklen_t socklen = sizeof(ss);
    char addrbuf[128];
    void *inaddr;
    const char *addr;
    int got_port = -1;
    fd = evhttp_bound_socket_get_fd(boundfd_);
    memset(&ss, 0, sizeof(ss));
    if (getsockname(fd, (struct sockaddr *)&ss, &socklen)) {
        perror("getsockname() failed");
        return 1;
    }
    if (ss.ss_family == AF_INET) {
        got_port = ntohs(((struct sockaddr_in*)&ss)->sin_port);
        inaddr = &((struct sockaddr_in*)&ss)->sin_addr;
    } else if (ss.ss_family == AF_INET6) {
        got_port = ntohs(((struct sockaddr_in6*)&ss)->sin6_port);
        inaddr = &((struct sockaddr_in6*)&ss)->sin6_addr;
    } else {
        fprintf(stderr, "Weird address family %d\n",
            ss.ss_family);
        return 1;
    }
    addr = evutil_inet_ntop(ss.ss_family, inaddr, addrbuf,
        sizeof(addrbuf));
    if (addr) {
        printf("Listening on %s:%d\n", addr, got_port);
        evutil_snprintf(uriRoot_, sizeof(uriRoot_),
            "http://%s:%d",addr,got_port);
    } else {
        fprintf(stderr, "evutil_inet_ntop failed\n");
        return 1;
    }
    event_base_dispatch(base_);

    return 0;
}
/**
 * @Brief    stop http service
 * @Method   stop
 * @DateTime 2018-07-19T18:31:32+0800
 * @Modify   2018-07-19T18:31:32+0800
 * @Author   Anyz
 * @Keyword
 * @return   [description]
 */
int http_server::stop() {
    
    return 0;
}
/**
 * @Brief    reply to request client 
 * @Method   replay
 * @DateTime 2018-07-20T14:32:51+0800
 * @Modify   2018-07-20T14:32:51+0800
 * @Author   Anyz
 * @Keyword
 * @param    req [description]
 * @param    code [description]
 * @param    reason [description]
 * @param    content [description]
 * @return   [description]
 */
int http_server::reply(const EvHttpRequest* req, int code, const char* reason, const char* content) {
    struct evbuffer* buff;
    buff = evbuffer_new();
    evbuffer_add_printf(buff,"%s\n", content);
    evhttp_send_reply(const_cast<EvHttpRequest*>(req), code, reason, buff);
    evbuffer_free(buff);
    return 0;
}
/**
 * @Brief    reply to request for binary stream
 * @Method   send
 * @DateTime 2018-07-20T14:32:51+0800
 * @Modify   2018-07-20T14:32:51+0800
 * @Author   Anyz
 * @Keyword
 * @param    req [description]
 * @param    code [description]
 * @param    reason [description]
 * @param    buffdata [description]
 * @param    len
 * @return   [description]
 */
int http_server::send(const EvHttpRequest* req, int code, const char* reason, char* buffdata, int len) {
    struct evbuffer* buff;
    buff = evbuffer_new();
    evbuffer_add(buff, buffdata, len);
    evhttp_send_reply(const_cast<EvHttpRequest*>(req), code, reason, buff);
    evbuffer_free(buff);
    return 0;
}
/**
 * @Brief
 * @Method   cleanup
 * @DateTime 2018-07-19T18:31:29+0800
 * @Modify   2018-07-19T18:31:29+0800
 * @Author   Anyz
 * @Keyword
 * @return   [description]
 */
void http_server::cleanup() {
#if defined(_WIN32) || defined(_WIN64)
    WSACleanup();
#endif
    event_base_free(base_);
}
/**
 * @Brief    get http request action type name
 * @Method   action request type
 * @DateTime 2018-07-20T14:32:56+0800
 * @Modify   2018-07-20T14:32:56+0800
 * @Author   Anyz
 * @Keyword
 * @param    req [description]
 * @return   [description]
 */
const char* http_server::commandType(EvHttpRequest* req) const {
    switch (evhttp_request_get_command(req)) {
    case EVHTTP_REQ_GET:
        return "GET";
    case EVHTTP_REQ_POST:
        return "POST";
    case EVHTTP_REQ_HEAD:
        return "HEAD";
    case EVHTTP_REQ_PUT:
        return "PUT";
    case EVHTTP_REQ_DELETE:
        return "DELETE";
    case EVHTTP_REQ_OPTIONS:
        return "OPTIONS";
    case EVHTTP_REQ_TRACE:
        return "TRACE";
    case EVHTTP_REQ_CONNECT:
        return "CONNECT";
    case EVHTTP_REQ_PATCH:
        return "PATCH"; 
    default:
        return "unknown";
    }
    return "GET";
}

std::string  http_server::localAddress() {
    char ip[20] = {'\0'};
#if defined(_WIN32) || defined(_WIN64)
    char szHost[256];
    ::gethostname(szHost, 256);
    hostent* hostname = ::gethostbyname(szHost);
    in_addr addr;
    for (int i = 0; ; i++) {
        char* p = hostname->h_addr_list[i];
        if (p == NULL)
            break;
        memcpy(&addr.S_un.S_addr, p, hostname->h_length);
        char* ip = ::inet_ntoa(addr);
        printf("Local IP£º %s \n", ip);
        memcpy(localaddr_, ip, strlen(ip)+1);
        return std::string(ip);
    }
#else
    memset(ip, 0, sizeof(ip));
    const char* shellstr = "ifconfig | sed -n '2p' | awk -F'[ :]+' '{printf $4}'";  
    FILE* fp = popen(shellstr, "r");
    size_t bytes = fread(ip, sizeof(char), sizeof(ip), fp);
    if (bytes > 0) {
        ip[bytes] = '\0';
    }
    if (bytes < 8) {
        printf("IP address invalid.\n");
        pclose(fp);
        return "";
    }
    if (strlen(ip) > 0) {
        strcpy(localaddr_, ip);
    }
    pclose(fp);
#endif
    return std::string(ip);
}

std::string http_server::hostip() const {
    return localaddr_;
}

int http_server::port() const {
    return port_;
}
