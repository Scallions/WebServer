//
// Created by Scallions on 2021/4/8.
//

#include "HttpServer.hpp"
#include "Handler.hpp"


HttpServer::HttpServer(EventLoop *loop, int port, int threadNum) :
        loop_(loop), port_(port), threadNum_(threadNum),
        server_(loop_, port_, threadNum_)
{
    // 设置 server_ 处理函数
//    server_;
    setUpServerHandler(*this);
    for(auto it = resource_.begin(); it != resource_.end(); it++) {
        allResources_.push_back(it);
    }
    for(auto it = defaultResource_.begin(); it != defaultResource_.end(); it++) {
        allResources_.push_back(it);
    }
}

HttpServer::~HttpServer() {

}

void HttpServer::onNewConnection(EventLoop* nextLoop) {
    // 生成新的http连接
    int listenFd = server_.getFd();
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    socklen_t client_addr_len = sizeof(client_addr);
    int accept_fd = 0;
    accept_fd = accept(listenFd, (struct sockaddr *)&client_addr,&client_addr_len);
    std::cout << "new conn fd: " << accept_fd << " listen addr: " << inet_ntoa(client_addr.sin_addr)<<":"<<ntohs(client_addr.sin_port) << std::endl;
    SP_Connection conn{new Connection(nextLoop, accept_fd)};
    SP_HttpConnection httpConn{new HttpConnection(nextLoop, conn)};
    nextLoop->addConnection(conn);
    //conns_[fd] = httpConn;
    // 设置回调
    httpConn->setRequestCB(std::bind(&HttpServer::onRequest, this, httpConn));
    httpConn->setResponseCB(std::bind(&HttpServer::onResponse, this, httpConn));
    httpConn->setCloseCB(std::bind(&HttpServer::onClose, this, httpConn));

}

void HttpServer::onRequest(SP_HttpConnection conn) {
    HttpData& request = conn->getData();
    for(auto res_it: allResources_) {
        std::regex e(res_it->first);
        std::smatch sm_res;
        if(std::regex_match(request.path_, sm_res, e)) {
            if(res_it->second.count(request.method_)>0) {
                request.path_match_ = move(sm_res);
                res_it->second[request.method_](request);
                onResponse(conn);
                return;
            }
        }
    }
}

void HttpServer::start() {
    server_.start();
    server_.setNewConnCb(std::bind(&HttpServer::onNewConnection, this, std::placeholders::_1));
}

void HttpServer::onResponse(SP_HttpConnection conn) {
    HttpData& request = conn->getData();
    send(conn->getFd(), request.response_.c_str(), request.response_.size(), 0);
//    std::cout << request.response_.c_str() << std::endl<<"sizeof: "<< request.response_.size() <<std::endl;
//    conn->close();
}

void HttpServer::onClose(SP_HttpConnection conn) {

}
