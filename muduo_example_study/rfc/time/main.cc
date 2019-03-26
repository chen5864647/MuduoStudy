#include "timeser.hpp"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

int main() {

    LOG_INFO << "pid = " << getpid();
    muduo::net::EventLoop loop;
    muduo::net::InetAddress serAddr(2019);

    TimeServer timeserver(&loop, serAddr);
    timeserver.start();
    loop.loop();
    
    return 0;
}