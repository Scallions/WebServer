//
// Created by Scallions on 2021/4/7.
//

#include "EventLoopThread.hpp"

EventLoopThread::EventLoopThread() : exiting_(false), thread_(), mutex_(), cond_(), loop_() {

}

EventLoopThread::~EventLoopThread() {

}

void EventLoopThread::startLoop() {
    thread_.start();
    {
        std::unique_lock<std::mutex> lck(mutex_);
        cond_.wait(lck, [this](){return loop_!=nullptr});

    }
}

void EventLoopThread::threadFunc() {

}
