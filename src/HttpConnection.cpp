//
// Created by Scallions on 2021/4/8.
//


#include "HttpConnection.hpp"

HttpConnection::HttpConnection(EventLoop* loop, std::shared_ptr<Connection> conn):
    loop_(loop),
    conn_(std::move(conn))
{
    conn_->setReadCallback(std::bind(&HttpConnection::onRequest, this));
    conn_->setWriteCallback(std::bind(&HttpConnection::onResponse, this));
}

HttpConnection::~HttpConnection() {

}

void HttpConnection::onRequest() {
    int fd = conn_->getFd();
    // read data TODO: 怎么读 怎么读
    char buf[65536] = {0};
    int cnt = 0;
    cnt = recv(fd, buf, sizeof(buf),0);
    if(cnt==-1){
        std::cout<<"read error"<<std::endl;
//        conn_->setRevents( EPOLLIN );
        onClose();
    }else if(cnt==0){
        std::cout<<"remote close"<<std::endl;
        // handle close TODO: close
        onClose();
    }else {
        std::string content(buf);
        int idx = content.find("\r\n\r\n");
        std::istringstream stream(content.substr(0, idx + 1));
        parseRequest(std::move(stream));

        // cb
        if (requestCallback_) requestCallback_();
    }
}

void HttpConnection::onResponse() {
    if( responseCallback_ ) responseCallback_();
}

void HttpConnection::onClose() {
    loop_->removeConnection(conn_);
    if( closeCallback_ ) closeCallback_();
}

void HttpConnection::parseRequest(std::istringstream stream) {
    std::regex e("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
    std::smatch sub_match;

    std::string line;
    std::getline(stream, line);
    line.pop_back();
    if(std::regex_match(line, sub_match, e)) {
        data_.method_        = sub_match[1];
        data_.path_          = sub_match[2];
        data_.http_version_ = sub_match[3];

        bool matched;
        e="^([^:]*): ?(.*)$";
        // 解析头部的其他信息
        do {
            getline(stream, line);
            line.pop_back();
            matched=std::regex_match(line, sub_match, e);
            if(matched) {
                data_.headData_[sub_match[1]] = sub_match[2];
            }

        } while(matched==true);
    }
}

void HttpConnection::close() {
    loop_->removeConnection(conn_);
}



