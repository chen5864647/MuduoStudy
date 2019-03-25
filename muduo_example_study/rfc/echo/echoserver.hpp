#ifndef _ECHOSERVER_HPP_
#define _ECHOSERVER_HPP_

#include <muduo/net/TcpServer.h>

class EchoServer
{
public:
    EchoServer(muduo::net::EventLoop *loop, 
         const muduo::net::InetAddress listenAddr);
    
    ~EchoServer() = default;

    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr &conn);

    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                   muduo::net::Buffer *buf,
                   muduo::Timestamp &time);

    muduo::net::TcpServer _server;

};

#endif  // _ECHO_HPP_