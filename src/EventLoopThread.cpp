//
// Created by Scallions on 2021/4/7.
//

#include "EventLoopThread.hpp"

EventLoopThread::EventLoopThread() : exiting_(false), thread_(), mutex_(), cond_(), loop_() {

}

EventLoopThread::~EventLoopThread() {

}

EventLoop* EventLoopThread::startLoop() {
    std::function<void()> threadfun = std::bind(&EventLoopThread::threadFunc, this);
    thread_ = std::thread{threadfun};
    EventLoop *loop = nullptr;
    {
        std::unique_lock<std::mutex> lck(mutex_);
        cond_.wait(lck, [this](){return loop_!=nullptr;});
        loop = loop_;
    }
    return loop;
}

void EventLoopThread::threadFunc() {
    EventLoop loop;

    {
        std::unique_lock<std::mutex> lck(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }
    loop.loop();

    std::unique_lock<std::mutex> lck(mutex_);
    loop_ = nullptr;
}
