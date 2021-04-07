//
// Created by Scallions on 2021/4/7.
//

#ifndef MYSERVER_EPOLL_HPP
#define MYSERVER_EPOLL_HPP

#include <sys/epoll.h>
#include <unordered_map>
#include <vector>
#include "Connection.hpp"

class Epoll {
public:
    Epoll();
    ~Epoll();
    void add(SP_Connection req, int timeout);
    void mod(SP_Connection req, int timeout);
    void del(SP_Connection req);

    void poll(int time, std::vector<SP_Connection> &connList);
    int getEpollFd() { return epollFd_; }
//    void handleExpired(); // 处理超时

private:
    static const int MAXFDS = 100000;
    int epollFd_;
};


#endif //MYSERVER_EPOLL_HPP
