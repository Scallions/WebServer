//
// Created by Scallions on 2021/4/5.
//

#ifndef MYSERVER_BASESERVER_HPP
#define MYSERVER_BASESERVER_HPP

#include "Acceptor.hpp"
#include "EventLoop.hpp"
#include "EventLoopThreadPool.hpp"

class BaseServer{
//    ConnectionCallback ConnectionCallback_;
    using ReadCallback = std::function<void()>; // TODO: 接口未定义
    using WriteCallback = std::function<void()>;
    using NewConnCallback = std::function<void(EventLoop*)>;
public:
    // ctor
    BaseServer(EventLoop *loop, int port, int thread);
    ~BaseServer();
    // dtor
    void start();
    void close();
    void setReadCb(ReadCallback cb){ readCallback_ = cb;}
    void setWriteCb(WriteCallback cb){ writeCallback_ = cb;}
    void setNewConnCb(NewConnCallback cb){newConnCallback_ = cb;}

    int getFd(){return listenFd_;}
private:
    int port_;
    int listenFd_;
    int thread_;
    EventLoop *loop_; // acceptor loop
    EventLoopThreadPool pool_;
    Acceptor acceptor_;
    // conn 的回调函数
    ReadCallback readCallback_;
    WriteCallback writeCallback_;
    NewConnCallback newConnCallback_;

    void onNewConnection();
};


#endif //MYSERVER_BASESERVER_HPP
