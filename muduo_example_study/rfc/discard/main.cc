#include "discard.hpp"

#include <muduo/net/EventLoop.h>

int main() {

    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr(2019);
    
    Discard discard(&loop, addr);
    discard.start();

    loop.loop();

    return 0;
}