//
// Created by Scallions on 2021/4/5.
//

#include "BaseServer.hpp"
#include <iostream>

BaseServer::BaseServer(int port, int thread, EventLoop *loop) : port_(port), thread_(thread), loop_(loop){
    acceptor_ = Acceptor(loop_, port_);
    acceptor_.setNe
}

BaseServer::~BaseServer(){
    std::cout<<"Destroy"<<std::endl;
}

void BaseServer::start(){
    std::cout<<"Start"<<std::endl;
}

void BaseServer::close(){
    std::cout<<"Close"<<std::endl;
}


