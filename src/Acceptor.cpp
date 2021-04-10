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
//    fcntl(listenFd_, F_SETFL,fcntl(listenFd_, F_GETFL, 0) | SO_REUSEPORT);
    std::cout << "Create acceptor: "<< listenFd_ << std::endl;
    int val=1;
    setsockopt(listenFd_, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));
    sockaddr_in serv_addr;
    memset(&serv_addr, sizeof(serv_addr), 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
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
    if(newConnectionCallback_){
        newConnectionCallback_();
    }
}
