// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#ifndef THREADPOOL_EPOLL_SOCKET_H
#define THREADPOOL_EPOLL_SOCKET_H

#include "InetAddress.h"
#include "../threadpool/Noncopyable.h"

namespace Henry {
    typedef struct sockaddr SA;

    class Socket : Noncopyable {
    public:
        explicit Socket(int sockfd);
        ~Socket();

        int fd() const;
        void bindAddress(const InetAddress &addr);
        void listen();
        int accept();

        void shutdownWrite();

        void setTcpNoDelay(bool on);
        void setReusePort(bool on);
        void setReuseAddr(bool on);
        void setKeepAlive(bool on);

        static InetAddress getLocalAddr(int sockfd);
        static InetAddress getPeerAddr(int sockfd);

    private:
        const int sockfd;
    };
}

#endif //THREADPOOL_EPOLL_SOCKET_H
