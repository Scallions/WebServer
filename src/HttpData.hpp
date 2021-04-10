//
// Created by Scallions on 2021/4/8.
//

#ifndef MYSERVER_HTTPDATA_HPP
#define MYSERVER_HTTPDATA_HPP

#include <map>
#include <regex>

using HeadMap = std::map<std::string,std::string>;


class HttpData {
public:
    std::string method_;
    std::string path_;
    std::string http_version_;
    std::string filename_;
    std::shared_ptr<std::istream> content_;
    std::smatch path_match_;
    std::string response_;
    HeadMap headData_;
private:
};


#endif //MYSERVER_HTTPDATA_HPP
