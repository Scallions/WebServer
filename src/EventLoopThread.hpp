//
// Created by Scallions on 2021/4/7.
//

#ifndef MYSERVER_EVENTLOOPTHREAD_HPP
#define MYSERVER_EVENTLOOPTHREAD_HPP


#include "EventLoop.hpp"

class EventLoopThread {
public:
    EventLoopThread();
    ~EventLoopThread();
    void startLoop();

private:
    bool exiting_;
    Thread thread_;
    Mutex mutex_;
    Condition cond_;
    EventLoop loop_;

    void threadFunc();
};


#endif //MYSERVER_EVENTLOOPTHREAD_HPP
