#include <string>
#include <muduo/base/Logging.h>

#include "chargenserver.hpp"

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

ChargenServer::ChargenServer(EventLoop *loop,
                            const InetAddress &listenAddr)
: server_(loop, listenAddr, "Chargen") {

    server_.setConnectionCallback(
        std::bind(&ChargenServer::onConnection, this, _1)
    );

    server_.setMessageCallback(
        std::bind(&ChargenServer::onMessage, this, _1, _2, _3)
    );

    server_.setWriteCompleteCallback(
        std::bind(&ChargenServer::onWriteComplete, this, _1)
    );
}

void ChargenServer::onConnection(const TcpConnectionPtr &conn) {
    LOG_INFO << "ChargenServer - " << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " is "
            << (conn->connected() ? "up" : "down");

    if (conn->connected()) {
        conn->setTcpNoDelay(true);
        conn->send(message_);
    }
}

void ChargenServer::onMessage(const TcpConnectionPtr &conn,
                            Buffer *buff,
                            Timestamp time) {
    LOG_INFO << conn->name() << " discards " << msg.size()
            << " bytes received at " << time.toString();
}

void ChargenServer::onWriteComplete(const TcpConnectionPtr &conn) {
    transferred_ += message_.size();
    conn->send(message_);
}