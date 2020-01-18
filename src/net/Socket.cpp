// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

//#include "Socket.h"
#include "../../include/net/Socket.h"
#include "Log4Func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>

namespace Henry {
    Socket::Socket(int sockfd) : sockfd(sockfd) {}

    Socket::~Socket() {
        ::close(sockfd);
    }

#if 0
    void Socket::read(const InetAddress &inetAddress)
    {
        setReuseAddr(true);
        setReusePort(true);
        setKeepAlive(true);
        setTcpNoDelay(true);
        bindAddress(inetAddress);
        listen();
    }
#endif

    void Socket::bindAddress(const InetAddress &addr) {
        if (::bind(sockfd, (SA *)addr.getSockAddrInet(), sizeof(addr)) == -1) {
            LogError("Socket::bindAddress bind address error!");
            exit(EXIT_FAILURE);
        }
    }

    int Socket::accept() {
        int fd = ::accept(sockfd, NULL, NULL);
        if (fd == -1) {
            LogError("Socket::accept() accept error!");
            exit(EXIT_FAILURE);
        }
    }

    void Socket::shutdownWrite() {
        if (::shutdown(sockfd, SHUT_WR) == -1) {
            LogError("Socket::shutdownWrite() shutdown error!");
            exit(EXIT_FAILURE);
        }
    }

    void Socket::setTcpNoDelay(bool on) {
        int optval = on ? 1 : 0;
        if (::setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &optval,
                         static_cast<socklen_t >(sizeof(optval))) == -1) {
            LogError("Socket::setTcpNoDelay error!");
            exit(EXIT_FAILURE);
        }
    }

    void Socket::setReuseAddr(bool on) {
        int optval = on ? 1 : 0;
        if (::setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval,
                         static_cast<socklen_t >(sizeof(optval))) == -1) {
            LogError("Socket::setReuseAddr error!");
            exit(EXIT_FAILURE);
        }
    }

    void Socket::setReusePort(bool on) {
#ifdef SO_REUSEPORT
        int optval = on ? 1 : 0;
        int ret = ::setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval,
                         static_cast<socklen_t >(sizeof(optval)));
        if(ret < 0){
            LogError("Socket::setReusePort error!");
            exit(EXIT_FAILURE);
        }
#else
        if(on)
            LogError("Socket::setReusePort SO_REUSEPORT is not supported!");
#endif
    }

    void Socket::setKeepAlive(bool on) {
        int optval = on ? 1 : 0;
        if (::setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval,
                         static_cast<socklen_t >(sizeof(optval))) == -1) {
            LogError("Socket::setKeepAlive error!");
            exit(EXIT_FAILURE);
        }
    }

    InetAddress Socket::getLocalAddr(int sockfd) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        if(::getsockname(sockfd,(SA*)&addr,&len) == Error)
        {
            LogError("Socket::getLocalAddr error!");
            exit(EXIT_FAILURE);
        }
        return InetAddress(addr);  //return this
    }

    InetAddress Socket::getPeerAddr(int sockfd){
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        if(::getpeername(sockfd,(SA*)&addr,&len) == Error)
        {
            LogError("Socket::getPeerAddr error!");
            exit(EXIT_FAILURE);
        }
        return InetAddress(addr);  //return this
    }

    void Socket::listen() {
        if(::listen(sockfd,5) == Error)
        {
            LogError("Socket::listen() listen address error!");
            exit(EXIT_FAILURE);
        }
    }

    int Socket::fd() const
    {
        return sockfd;
    }
}