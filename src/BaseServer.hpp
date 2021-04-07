//
// Created by Scallions on 2021/4/5.
//

#ifndef MYSERVER_BASESERVER_HPP
#define MYSERVER_BASESERVER_HPP

#include "Acceptor.hpp"
#include "EventLoop.hpp"
#include "EventLoopThreadPool.hpp"

class BaseServer{

public:
    // ctor
    BaseServer(int port, int thread, EventLoop *loop);
    ~BaseServer();
    // dtor
    void start();
    void close();

private:
    int port_;
    int listen_;
    int thread_;
    Acceptor acceptor_;
    EventLoop *loop_; // acceptor loop
    EventLoopThreadPool pool_;
    NewConnectionCallback newConnectionCallback_;
    ReadCallback readCallback_;
    WriteCallback writeCallback;_;
};


#endif //MYSERVER_BASESERVER_HPP
