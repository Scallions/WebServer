//
// Created by Scallions on 2021/4/7.
//

#ifndef MYSERVER_EVENTLOOP_HPP
#define MYSERVER_EVENTLOOP_HPP

#include <mutex>
#include <vector>
#include <functional>
#include "Epoll.hpp"
#include "Connection.hpp"

class Connection;
class Epoll;

class EventLoop {

public:
    using Functor = std::function<void()>;
    using SP_Connection = std::shared_ptr<Connection>;
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();
    // 处理connection
    void addConnection(SP_Connection conn);
    void updateConnection(SP_Connection conn);
    void removeConnection(SP_Connection conn);

    // 处理队列事件
    void runInLoop(Functor);
    void queueInLoop(Functor);

private:
    bool looping_;  // 是否在循环
    std::unique_ptr<Epoll> poller_; // 控制io
    bool quit_;
    std::mutex mutex_;
    std::vector<Functor> funcList_; // 函数队列
    std::vector<SP_Connection> connList_;
//    pid_t thread_;

    void doPendingFunc();
};


#endif //MYSERVER_EVENTLOOP_HPP
