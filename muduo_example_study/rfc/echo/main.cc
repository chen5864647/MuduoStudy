#include <unistd.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include "echoserver.hpp"

int main() {

    LOG_INFO << "pid = " << getpid();
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr(2007);
    EchoServer echo(&loop, listenAddr);
    echo.start();
    loop.loop();

    return 0;
}