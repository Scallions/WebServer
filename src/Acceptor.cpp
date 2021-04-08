//
// Created by Scallions on 2021/4/7.
//


#include "Acceptor.hpp"


Acceptor::Acceptor(EventLoop *loop, int port) :
    loop_(loop),
    listenFd_(socket(PF_INET, SOCK_STREAM, 0)),
    acceptConnection_(new Connection(loop_, listenFd_))
{

    // 设置监听socket
    std::cout << "Create acceptor: "<< listenFd_ << std::endl;
    if(listenFd_ < 0 ){
        std::cout << "Create - listen socket: " << listenFd_ << std::endl;
    }
    sockaddr_in serv_addr;
    memset(&serv_addr, sizeof(serv_addr), 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    fcntl(listenFd_, F_SETFL,fcntl(listenFd_, F_GETFL, 0) | SO_REUSEPORT);
    bind(listenFd_, reinterpret_cast<const sockaddr *>(&serv_addr), sizeof(serv_addr));

    // 设置connection
    acceptConnection_->setReadCallback(
            std::bind(&Acceptor::handleRead, this)
            );
}

Acceptor::~Acceptor() {

}

void Acceptor::listening() {
    std::cout << "start listening"<< std::endl;
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
