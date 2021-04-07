//
// Created by Scallions on 2021/4/7.
//

#include "Epoll.hpp"

Epoll::Epoll(): epollFd_(epoll_create1(EPOLL_CLOEXEC)) {

}

Epoll::~Epoll() {}

void Epoll::add(SP_Connection req, int timeout) {
    int fd = req->getFd();
    if (timeout > 0){
        add_timer
    }
}
