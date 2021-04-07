//
// Created by Scallions on 2021/4/7.
//

#ifndef MYSERVER_CALLBACKS_HPP
#define MYSERVER_CALLBACKS_HPP

#include <functional>

using CloseCallback std::function<void (const TcpConnectionPtr&)>;
using WriteCallback std::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;
typedef std::function<void (const TcpConnectionPtr&, size_t)> HighWaterMarkCallback;

#endif //MYSERVER_CALLBACKS_HPP
