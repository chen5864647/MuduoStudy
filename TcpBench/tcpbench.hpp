#ifndef _TCPBENCH_HPP_
#define _TCPBENCH_HPP_

#include "unp.hpp"


class TcpBench {

public:
    TcpBench() = default;
    TcpBench(std::string shost, int clientPort) 
        : shost(shost), clientPort(clientPort) { }
    
    void setPort(int clientPort);

    void setHost(std::string shost);

    void setHostAndPort(std::string shost, int clientPort);

    virtual ~TcpBench() { }

    int Socket();

private:

    // const char *chost;
    std::string shost;
    int clientPort;
    

};

#endif  // _TCPBENCH_HPP_