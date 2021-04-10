//
// Created by Scallions on 2021/4/8.
//

#ifndef MYSERVER_HTTPCONNECTION_HPP
#define MYSERVER_HTTPCONNECTION_HPP


#include <memory>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <regex>

#include "HttpData.hpp"
#include "Connection.hpp"
#include "EventLoop.hpp"

class EventLoop;
class Connection;

class HttpConnection {
    using RequestCallback = std::function<void()>;
    using ResponseCallback = std::function<void()>;
    using CloseCallback = std::function<void()>;
public:
    HttpConnection(EventLoop* loop, std::shared_ptr<Connection> conn);
    ~HttpConnection();

    void setRequestCB(RequestCallback cb){requestCallback_ = cb;};
    void setResponseCB(ResponseCallback cb){responseCallback_ = cb;}
    void setCloseCB(CloseCallback cb){ closeCallback_ = cb;}

    int getFd(){ return conn_->getFd();}

    void close();

    HttpData& getData(){return data_;}
private:
    EventLoop* loop_;
    std::shared_ptr<Connection> conn_;
    HttpData data_;
    RequestCallback requestCallback_;
    ResponseCallback responseCallback_;
    CloseCallback closeCallback_;

    void onRequest();
    void onResponse();
    void parseRequest(std::istringstream stream);

    void onClose();


};

using SP_HttpConnection = std::shared_ptr<HttpConnection>;
#endif //MYSERVER_HTTPCONNECTION_HPP
