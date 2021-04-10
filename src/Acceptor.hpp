//
// Created by Scallions on 2021/4/7.
//

/*
 * 主要是维护监听fd，并提供给外部新链接进来是调用的接口
 */
#ifndef MYSERVER_ACCEPTOR_HPP
#define MYSERVER_ACCEPTOR_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <functional>
#include <memory>
#include <fcntl.h>
#include "EventLoop.hpp"
//#include "Connection.hpp"

//class EventLoop;
class Connection;

class Acceptor {
public:
    using NewConnectionCallback = std::function<void()>;
    Acceptor() = default;
    Acceptor(EventLoop *loop, int port);
    ~Acceptor();

    void listening();
    void handleRead();
    void setNewConnectionCallback(const NewConnectionCallback &cb){
        newConnectionCallback_ = cb;
    }

    int getFd(){return listenFd_;}
private:
    EventLoop *loop_;
    int listenFd_;
    SP_Connection acceptConnection_;
    NewConnectionCallback newConnectionCallback_;
};


#endif //MYSERVER_ACCEPTOR_HPP
