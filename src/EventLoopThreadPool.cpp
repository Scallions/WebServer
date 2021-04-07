//
// Created by Scallions on 2021/4/7.
//

#include "EventLoopThreadPool.hpp"

EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, int numThreads) :
    baseLoop_(baseLoop),
    numThreads_(numThreads),
    next_(0)
{
}

EventLoopThreadPool::~EventLoopThreadPool(){

}

void EventLoopThreadPool::start() {
    for (int i = 0; i < numThreads_; ++i)
    {
        EventLoopThread* t = new EventLoopThread();
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));
        loops_.push_back(t->startLoop());
    }
}

EventLoop *EventLoopThreadPool::getNextLoop() {
    EventLoop* loop = nullptr;
    if (!loops_.empty())
    {
        // round-robin
        loop = loops_[next_];
        ++next_;
        if (next_ >= loops_.size())
        {
            next_ = 0;
        }
    }
    return loop;
}
