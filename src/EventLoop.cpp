//
// Created by Scallions on 2021/4/7.
//

#include <cassert>
#include "EventLoop.hpp"

EventLoop::EventLoop() :
    looping_(false),
    poller_(new Epoll()),
    quit_(false),
    thread_()
{

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

void EventLoop::runInLoop(Functor cb) {
    queueInLoop(std::move(cb));
}

void EventLoop::queueInLoop(Functor cb) {
    std::unique_lock<std::mutex> mutex_;
    funcList_.push_back(std::move(cb));
}

void EventLoop::addConnection(SP_Connection conn) {
    std::cout<<"add conn: " << conn->getFd() << std::endl;
    poller_->add(conn, 0);
}
