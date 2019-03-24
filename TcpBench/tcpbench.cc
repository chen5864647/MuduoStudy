#include "tcpbench.hpp"

using namespace std;

int TcpBench::Socket()
{
    const char *host = (this->shost).c_str();
    
    int sock;
    unsigned long inaddr;
    struct sockaddr_in ad;
    struct hostent *hp;
    
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;    // IPv4

    inaddr = inet_addr(host);
    if (inaddr != INADDR_NONE)
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    else {
        hp = gethostbyname(host);
        if (hp == nullptr || hp == NULL)
            return -1;
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }

    ad.sin_port = htons(clientPort);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return sock;

    if (connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)
        return -1;

    return sock;
}


inline 
void TcpBench::setPort(int clientPort) {
    this->clientPort = clientPort;
}

inline 
void TcpBench::setHost(string shost) {
    this->shost = shost;
}

inline void TcpBench::setHostAndPort(string shost, int clientPort) {
    this->shost = shost;
    this->clientPort = clientPort;
}

int main() {
    TcpBench tcpbench;

    return 0;
}