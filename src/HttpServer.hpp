//
// Created by Scallions on 2021/4/8.
//

#ifndef MYSERVER_HTTPSERVER_HPP
#define MYSERVER_HTTPSERVER_HPP

#include <functional>

#include "BaseServer.hpp"
#include "HttpConnection.hpp"
#include "EventLoop.hpp"

class EventLoop;
class HttpConnection;
using SP_HttpConnection = std::shared_ptr<HttpConnection>;



class HttpServer {
public:
    using ResourceType = std::map<std::string, std::unordered_map<std::string, std::function<void(HttpData&)>>>;
    ResourceType resource_;
    ResourceType defaultResource_;
    std::vector<ResourceType::iterator> allResources_;
    HttpServer(EventLoop* loop, int port, int threadNum);
    ~HttpServer();

    void start();

private:
    int port_;
    EventLoop* loop_;
    int threadNum_;
    BaseServer server_;

    //
    // std::map<int, SP_HttpConnection> conns_;

    void onNewConnection(EventLoop*);
    void onRequest(SP_HttpConnection coon);
    void onResponse(SP_HttpConnection conn);
    void onClose(SP_HttpConnection conn);
};


#endif //MYSERVER_HTTPSERVER_HPP
