#include "echo.hpp"

#include <muduo/base/Logging.h>
#include <cctype>
#include <string>

using namespace std::placeholders;

EchoServer::EchoServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr)
: server_(loop, listenAddr, "Echo") {

    server_.setConnectionCallback(
        std::bind(&EchoServer::onConnection, this, _1)
    );

    server_.setMessageCallback(
        std::bind(&EchoServer::onMessage, this, _1, _2, _3)
    );

}

void EchoServer::start() {
    this->server_.start();
}

void EchoServer::onConnection(const muduo::net::TcpConnectionPtr& conn) {

    LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "up" : "down");

}

void EchoServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time) {
    muduo::string msg(buf->retrieveAllAsString());

    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
           << "data received at " << time.toString();

    int add;
    std::string smsg(msg);
    for (char &ch : smsg) {
        if ('A' <= ch && ch <= 'Z') {
            add = ch - 'A';
            add += 13;
            add %= 26;
            ch = 'A' + add;

            ch = tolower(ch);
        }
        else if ('a' <= ch && ch <= 'z') {
            add = ch -'a';
            add += 13;
            add %= 26;
            ch = 'a' + add;

            ch = toupper(ch);
        }
    }
    
    conn->send(smsg);
    conn->shutdown();
}