#ifndef _DISCARD_HPP_
#define _DISCARD_HPP_

#include <muduo/net/TcpServer.h>

class Discard {
public:
    Discard(muduo::net::EventLoop *loop,
            const muduo::net::InetAddress &addr);

    ~Discard() = default;

    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr &conn);

    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                muduo::net::Buffer *buf,
                muduo::Timestamp time);

    muduo::net::TcpServer server_;

};

#endif  // _DISCARD_HPP_