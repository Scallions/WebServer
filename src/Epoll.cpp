//
// Created by Scallions on 2021/4/7.
//

#include <cstring>
#include "Epoll.hpp"

Epoll::Epoll():
    epollFd_(epoll_create1(EPOLL_CLOEXEC)),
    events_(16),
    conns_()
{
    std::cout << "create epoll fd: " << epollFd_ << std::endl;
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
    event.data.fd = fd;
    epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &event);
    conns_[fd] = req;
    std::cout << "epoll add: " << fd << std::endl;
}

void Epoll::poll(int time, std::vector<SP_Connection> &connList) {
    int numEvents = epoll_wait(epollFd_,
                                 &*events_.begin(),
                                 static_cast<int>(events_.size()),
                                 0);
    if(numEvents >0 ){
        std::cout << "epoll poll num: " << numEvents << std::endl;
        fillActivateConnection(connList, numEvents);
    }
}

void Epoll::fillActivateConnection(std::vector<SP_Connection> &connList, int numEvents) {
    for(int i=0; i<numEvents;++i){
        int fd = events_[i].data.fd;
        if(conns_.find(fd)!=conns_.end()){
//            connList[i] = conns_[fd];
            conns_[fd]->setRevents( events_[i].events);
            connList.push_back(conns_[fd]);
        }

    }
}
