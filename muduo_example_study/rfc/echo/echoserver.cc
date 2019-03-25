#include "echoserver.hpp"

#include <muduo/base/Logging.h>
#include <string>
#include <cctype>

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

EchoServer::EchoServer(muduo::net::EventLoop *loop, 
const muduo::net::InetAddress listenAddr) 
: _server(loop, listenAddr, "EchoServer") {
    _server.setConnectionCallback(
        std::bind(&EchoServer::onConnection, this, _1)
    );

    _server.setMessageCallback(
        std::bind(&EchoServer::onMessage, this, _1, _2, _3)
    );

}

void EchoServer::start() {
    _server.start();
}

void EchoServer::onConnection(const muduo::net::TcpConnectionPtr &conn) {
    
    LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "up" : "down");

}

void EchoServer::onMessage(const muduo::net::TcpConnectionPtr &conn,
muduo::net::Buffer *buf,
muduo::Timestamp &time) {
    
    muduo::string msg(buf->retrieveAllAsString());

    int add;
    for (char &ch : msg) {
        if ('a' <= ch && ch <= 'z') {
            // ROT13
            add = ch - 'a';
            add += 13;
            add %= 26;
            ch = (char) ('a' + add);

            // toupper
            ch = toupper(ch);
        }
        else if ('A' <= ch && ch <= 'Z') {
            // ROT13
            add = ch -'A';
            add += 13;
            add %= 26;
            ch = (char) ('A' + add);

            // tolower
            ch = tolower(ch);
        }
    }

    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
             << "data received at " << time.toString();

    conn->send(msg);

    conn->shutdown();
}