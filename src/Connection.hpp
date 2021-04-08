//
// Created by Scallions on 2021/4/7.
//

#ifndef MYSERVER_CONNECTION_HPP
#define MYSERVER_CONNECTION_HPP

#include <sys/epoll.h>
#include <memory>
#include <functional>
#include <iostream>
//#include "EventLoop.hpp" // 互相引用头文件= =

class EventLoop;

class Connection {
public:
    using EventCallback=std::function<void()>;
//    Connection(EventLoop *loop, int socketFd);
//    Connection(const Connection &) = default;
//
//    Connection & operator = (const Connection &) = default;
    Connection(EventLoop *loop, int fd);
    ~Connection();

    int getFd(){return fd_;}

    void handleEvent();

    // set callback func
    void setReadCallback(EventCallback cb);
    void setWriteCallback(EventCallback cb);

    void setRevents(int revt) { revents_ = revt;};
private:
    EventLoop *loop_;
    int fd_;
    int events_; // type
    int revents_; // received event types

    EventCallback readCallback_;
    EventCallback writeCallback_;
};


using SP_Connection = std::shared_ptr<Connection>;

#endif //MYSERVER_CONNECTION_HPP
