#include "discard.hpp"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

Discard::Discard(EventLoop *loop, const InetAddress &addr) 
: server_(loop, addr, "Discard") {

    this->server_.setConnectionCallback(
        std::bind(&Discard::onConnection, this, _1)
    );

    this->server_.setMessageCallback(
        std::bind(&Discard::onMessage, this, _1, _2, _3)
    );

}

void Discard::start() {
    this->server_.start();
}

void Discard::onConnection(const TcpConnectionPtr &conn) {
    LOG_INFO << "Discard - " << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " is "
            << (conn->connected() ? "up" : "down");

    if (!conn->connected()) {
        conn->shutdown();
    }
}

void Discard::onMessage(const TcpConnectionPtr &conn,
                    Buffer *buf, 
                    Timestamp time) {
    muduo::string msg(buf->retrieveAllAsString());

    LOG_INFO << conn->peerAddress().toIpPort() << " : "
            << msg << "...";
}