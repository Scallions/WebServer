//
// Created by Scallions on 2021/4/7.
//

#ifndef MYSERVER_EPOLL_HPP
#define MYSERVER_EPOLL_HPP

#include <sys/epoll.h>
#include <unordered_map>
#include <unistd.h>
#include <vector>
#include <map>
#include "Connection.hpp"

class Connection;

class Epoll {
public:
    using SP_Connection = std::shared_ptr<Connection>;

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
    using EventList = std::vector<epoll_event>;
    EventList events_;
    using ConnectionList = std::map<int, SP_Connection>;
    ConnectionList conns_;

    void fillActivateConnection(std::vector<SP_Connection> &connList, int numEvents);
};


#endif //MYSERVER_EPOLL_HPP
