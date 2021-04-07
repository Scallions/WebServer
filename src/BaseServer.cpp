//
// Created by Scallions on 2021/4/5.
//

#include "BaseServer.hpp"
#include <iostream>

BaseServer::BaseServer(int port, int thread, EventLoop *loop) :
    port_(port),
    thread_(thread),
    loop_(loop),
    pool_(loop,thread_)
{
    acceptor_ = Acceptor(loop_, port_);
    acceptor_.setNewConnectionCallback(std::bind(&BaseServer::onNewConnection, this, std::placeholders::_1));
}

BaseServer::~BaseServer(){
    std::cout<<"Destroy"<<std::endl;
}

void BaseServer::start(){
    std::cout<<"Start"<<std::endl;
    pool_.start();
    loop_->runInLoop(std::bind(&Acceptor::listening, &acceptor_));
}

void BaseServer::close(){
    std::cout<<"Close"<<std::endl;
}

void BaseServer::onNewConnection(int fd) {
    EventLoop* ioLoop = pool_.getNextLoop();
    SP_Connection conn{new Connection(ioLoop, fd)};
    conn->setReadCallback(readCallback_);
    conn->setWriteCallback(writeCallback_);
    loop_->addConnection(conn);
}


