//
// Created by Scallions on 2021/4/7.
//

#include <cstring>
#include "Epoll.hpp"

Epoll::Epoll():
    epollFd_(epoll_create1(EPOLL_CLOEXEC)),
    events_(16)
{
}

Epoll::~Epoll() {}

void Epoll::add(SP_Connection req, int timeout) {
    int fd = req->getFd();
//    if (timeout > 0){
//        add_timer
//    }
    epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN|EPOLLOUT;
    epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &event);
}

void Epoll::poll(int time, std::vector<SP_Connection> &connList) {
    size_t t = events_.size();
    int numEvents = epoll_wait(epollFd_,
                                 &*events_.begin(),
                                 static_cast<int>(events_.size()),
                                 0);
}
