#include <iostream>
#include "src/BaseServer.hpp"

int main() {
    EventLoop loop;
    BaseServer server(9999,4,&loop);
    server.start();
//    server.
    loop.loop();
    return 0;
}
