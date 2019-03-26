#include "timeser.hpp"

#include <muduo/base/Logging.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>
#include <string>
#include <iostream>

using namespace muduo::net;
using namespace std::placeholders;

TimeServer::TimeServer(EventLoop *loop, const InetAddress &serAddr) 
: server_(loop, serAddr, "Time") {

    server_.setConnectionCallback(
        std::bind(&TimeServer::onConnection, this, _1)
    );


}

void TimeServer::start() {
    this->server_.start();
}

void TimeServer::onConnection(const TcpConnectionPtr &conn) {
    
    LOG_INFO << "TimeServer - " << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " is "
            << (conn->connected() ? "up" : "down");
    
    if (conn->connected()) {
        time_t now = ::time(NULL);
        int32_t be32 = sockets::hostToNetwork32(static_cast<int32_t>(now));
        conn->send(&be32, sizeof be32);
        // conn->shutdown();
        if (conn->connected()) 
            conn->forceCloseWithDelay(20);
    }
}
