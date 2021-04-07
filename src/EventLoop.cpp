//
// Created by Scallions on 2021/4/7.
//

#include <cassert>
#include "EventLoop.hpp"

EventLoop::EventLoop() : thread_(CurrentThread::tid()) {

}

EventLoop::~EventLoop() {

}

void EventLoop::loop() {
    assert(!looping_);
    looping_ = true;
    quit_ = false;

    while(!quit_){
        // 处理 poller
        connList_.clear();
        poller_->poll(-1, connList_);

        for(auto conn: connList_){
            conn->handleEvent();
        }

        // 处理 funcList
        doPendingFunc();
    }
}

void EventLoop::quit() {
    quit_ = true;
}

void EventLoop::doPendingFunc() {
    std::vector<Functor> functors;

    {
        std::unique_lock<std::mutex> lck{mutex_};
        functors.swap(funcList_);
    }

    for(const auto &functor: functors){
        functor();
    }
}

void EventLoop::runInLoop() {

}

void EventLoop::queueInLoop() {

}
