#ifndef _CHARGEN_SERVER_HPP_
#define _CHARGEN_SERVER_HPP_

#include <muduo/net/TcpServer.h>

class ChargenServer {
public:
    ChargenServer(muduo::net::EventLoop *loop, 
                const muduo::net::InetAddress &listenAddr);
    void start();

private:
    muduo::net::TcpServer server_;

    void onConnection(const muduo::net::TcpConnectionPtr &conn);

    void onMessage(const muduo::net::TcpConnection &conn,
                    muduo::net::Buffer *buf,
                    muduo::Timestamp time);

    void onWriteComplete(const muduo::net::TcpConnectionPtr &conn);

};

#endif  // _CHARGEN_SERVER_HPP_