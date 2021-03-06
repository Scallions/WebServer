//
// Created by Scallions on 2021/4/7.
//

#include <sys/socket.h>
//#include <fcntl.h>
#include <unistd.h>
#include "Connection.hpp"

Connection::Connection(EventLoop *loop, int socketFd):
    loop_(loop),
    fd_(socketFd),
    events_(0),
    revents_(0) {

}

Connection::~Connection() {

}

void Connection::handleEvent() {
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        // close TODO: close cb
        loop_->removeConnection(SP_Connection{this});
        if(closeCallback_) closeCallback_();
    }
    if (revents_ & (EPOLLERR))
    {
        loop_->removeConnection(SP_Connection{this});
//        if (errorCallback_) errorCallback_(); // error TODO: error cb
    }
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        if (readCallback_) readCallback_();
    }
    if (revents_ & EPOLLOUT)
    {
        if (writeCallback_) writeCallback_();
    }
}

void Connection::setReadCallback(Connection::EventCallback cb) {
    readCallback_ = cb;
}

void Connection::setWriteCallback(Connection::EventCallback cb) {
    writeCallback_ = cb;
}

void Connection::setCloseCallback(Connection::EventCallback cb) {
    closeCallback_ = cb;
}
