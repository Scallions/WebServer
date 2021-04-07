//
// Created by Scallions on 2021/4/7.
//

#ifndef MYSERVER_EVENTLOOPTHREADPOOL_HPP
#define MYSERVER_EVENTLOOPTHREADPOOL_HPP


#include "EventLoop.hpp"
#include "EventLoopThread.hpp"

class EventLoopThreadPool {
public:
    EventLoopThreadPool(EventLoop* baseLoop, int numThreads);
    ~EventLoopThreadPool();

    void setTheardNum(int numThreads){ numThreads_ = numThreads;}
    void start();
    EventLoop* getNextLoop();
private:
    EventLoop* baseLoop_;
    int numThreads_;
    int next_;
    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;

};


#endif //MYSERVER_EVENTLOOPTHREADPOOL_HPP
