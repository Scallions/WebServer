//
// Created by Scallions on 2021/4/7.
//

#include "Connection.hpp"

Connection::Connection(EventLoop *loop, int socketFd): loop_(loop), fd_(socketFd), events_(0), revents_(0) {

}

Connection::~Connection() {

}

void Connection::handleEvent() {

}

void Connection::setReadCallback(Connection::EventCallback cb) {

}

void Connection::setWriteCallback(Connection::EventCallback cb) {

}
