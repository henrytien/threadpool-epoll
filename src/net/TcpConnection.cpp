// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#include "TcpConnection.h"
#include "Log4Func.h"
#include "EpollPoller.h"

namespace Henry {
    TcpConnection::TcpConnection(int sockfd, EpollPoller *p)
            : sockfd(sockfd), sockIO(sockfd), localAddr(Socket::getLocalAddr(sockfd)),
              peerAddr(Socket::getPeerAddr(sockfd)), isShutdownWrite(false), epollPoller(p) {}

    TcpConnection::~TcpConnection() {
        if(!isShutdownWrite)
        {
            shutdown();
        }
    }

#if 1
    void TcpConnection::handleConnectCallback() {
        if(onConnectionCallback)
        {
            onConnectionCallback(shared_from_this());
        }
    }
    void TcpConnection::handleMessageCallback(){
        if(onMessageCallback)
        {
            onMessageCallback(shared_from_this());
        }
    }
    void TcpConnection::handleCloseCallback(){
        if(onCloseCallback)
        {
            onCloseCallback(shared_from_this());
        }
    }
}
#endif

ssize_t TcpConnection::readn(char *buf, size_t count)
{
    ssize_t ret = sockIO.readn(buf,count);
    if(ret == -1)
    {
        LogError("stderr TcpConnection::readn");
        exit(EXIT_FAILURE);
    }
    return ret;
}


