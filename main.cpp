#include <iostream>
#include "src/HttpServer.hpp"

int main() {
    EventLoop loop;
    HttpServer server(&loop, 9999,4);
    server.start();
//    server.
    loop.loop();
    return 0;
}
