//
// Created by Scallions on 2021/4/5.
//

#include "BaseServer.hpp"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

BaseServer::BaseServer(EventLoop* loop, int port, int thread) :
    port_(port),
    listenFd_(0),
    thread_(thread),
    loop_(loop),
    pool_(loop_,thread_),
    acceptor_(loop_, port_)
{
    acceptor_.setNewConnectionCallback(std::bind(&BaseServer::onNewConnection, this));
    listenFd_ = acceptor_.getFd();
}

BaseServer::~BaseServer(){
    std::cout<<"Destroy"<<std::endl;
}

void BaseServer::start(){
    std::cout<<"Start server"<<std::endl;
    pool_.start();
    loop_->runInLoop(std::bind(&Acceptor::listening, &acceptor_));
}

void BaseServer::close(){
    std::cout<<"Close"<<std::endl;
}

void BaseServer::onNewConnection() {
//    std::cout<<"new conn: " << fd << std::endl;
    EventLoop* ioLoop = pool_.getNextLoop();
    if(newConnCallback_){
        newConnCallback_(ioLoop);
        return;
    }
//    SP_Connection conn{new Connection(ioLoop, fd)};
//    conn->setReadCallback(readCallback_);
//    conn->setWriteCallback(writeCallback_);
//    conn->setReadCallback([&conn]{
//        int fd = conn->getFd();
//        std::cout<<"Handle : " << fd << std::endl;
//        char buf[20]={0};
//        int cnt = 0;
//        cnt = recv(fd, buf, sizeof(buf),0);
//        if(cnt==-1){
//            std::cout<<"read error"<<std::endl;
//            conn->setRevents( EPOLLIN );
//        }else if(cnt==0){
//            std::cout<<"remote close"<<std::endl;
//            ::close(fd);
//        }else{
//            std::cout<<"read "<<buf<<std::endl;
//        }
//    });
//    conn->setWriteCallback([&conn]{
//        int fd_ = conn->getFd();
//        std::cout << "write to: " << fd_ << std::endl;
//        send(fd_, "Hello\n", 7,0);
//        std::cout<<"write hello"<<std::endl;
//    });
//    loop_->addConnection(conn);
}


