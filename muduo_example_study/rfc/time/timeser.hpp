#ifndef MUDUO_EXAMPLES_SIMPLE_TIME_TIME_HPP_
#define MUDUO_EXAMPLES_SIMPLE_TIME_TIME_HPP_

#include <muduo/net/TcpServer.h>

class TimeServer {
public:
    TimeServer(muduo::net::EventLoop *loop,
                const muduo::net::InetAddress &serAddr);

    ~TimeServer() = default;

    void start();

private:
    muduo::net::TcpServer server_;

    void onConnection(const muduo::net::TcpConnectionPtr &conn);

};

#endif  // MUDUO_EXAMPLES_SIMPLE_TIME_TIME_HPP_