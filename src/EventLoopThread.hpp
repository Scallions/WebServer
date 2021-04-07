//
// Created by Scallions on 2021/4/7.
//

#ifndef MYSERVER_EVENTLOOPTHREAD_HPP
#define MYSERVER_EVENTLOOPTHREAD_HPP

#include <thread>
#include <mutex>
#include <condition_variable>

#include "EventLoop.hpp"

class EventLoopThread {
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startLoop();

private:
    bool exiting_;
    std::thread thread_;
    std::mutex mutex_;
    std::condition_variable cond_;
    EventLoop *loop_;

    void threadFunc();
};


#endif //MYSERVER_EVENTLOOPTHREAD_HPP
