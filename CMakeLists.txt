cmake_minimum_required(VERSION 3.10)
project(myserver)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_LD_FLAGS "-lpthread")
#set_target_properties(${TARGET} PROPERTIES
#        COMPILE_FLAGS "-pthread"
#        LINK_FLAGS "-pthread")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(myserver main.cpp src/BaseServer.hpp src/BaseServer.cpp src/Acceptor.cpp src/Acceptor.hpp src/EventLoop.cpp src/EventLoop.hpp src/EventLoopThreadPool.cpp src/EventLoopThreadPool.hpp src/Connection.cpp src/Connection.hpp src/EventLoopThread.cpp src/EventLoopThread.hpp src/Epoll.cpp src/Epoll.hpp src/Callbacks.hpp)
target_link_libraries(myserver PUBLIC Threads::Threads)
