//
// Created by Scallions on 2021/4/7.
//


#include "Acceptor.hpp"


Acceptor::Acceptor(EventLoop *loop, int port) : loop_(loop) {

    // 创建监听socket
    listenFd_ = socket(PF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_addr;
    memset(&serv_addr, sizeof(serv_addr), 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = port;
    bind(listenFd_, reinterpret_cast<const sockaddr *>(&serv_addr), sizeof(serv_addr));

    acceptConnection_(loop_, listenFd_);
    acceptConnection_.setReadCallback(
            std::bind(&Acceptor::handleRead, this)
            );

}

Acceptor::~Acceptor() {

}

void Acceptor::listening() {
    listen(listenFd_, 5);
    loop_->addConnection(acceptConnection_);
}

void Acceptor::handleRead() {
    int connfd = accept(listenFd_, NULL, NULL);
    if(connfd>=0){
        if(newConnectionCallback_){
            newConnectionCallback_(connfd);
        }
    }
}
