cmake_minimum_required(VERSION 3.10)
project(myserver)

set(CMAKE_CXX_STANDARD 11)

add_executable(myserver main.cpp src/BaseServer.hpp src/BaseServer.cpp src/Acceptor.cpp src/Acceptor.hpp src/EventLoop.cpp src/EventLoop.hpp src/EventLoopThreadPool.cpp src/EventLoopThreadPool.hpp src/Connection.cpp src/Connection.hpp src/EventLoopThread.cpp src/EventLoopThread.hpp src/Epoll.cpp src/Epoll.hpp src/Callbacks.hpp)