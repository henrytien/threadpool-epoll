// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#ifndef THREADPOOL_EPOLL_TCPSERVER_H
#define THREADPOOL_EPOLL_TCPSERVER_H

#include "Noncopyable.h"
#include "EpollPoller.h"
#include "Socket.h"

namespace Henry {
    class TcpServer : Noncopyable {
    public:
        typedef EpollPoller::EpollCallback TcpServerCallback;

        TcpServer(const string &ip, unsigned short port);

        void start() {
            poller.loop();
        }

        void setConnectCallback(TcpServerCallback cb) {
            poller.setConnectCallback(std::move(cb));
        }

        void setMessageCallback(TcpServerCallback cb) {
            poller.setMessageCallback(std::move(cb));
        }

        void setCloseCallback(TcpServerCallback cb) {
            poller.setCloseCallback(std::move(cb));
        }

    private:
        InetAddress addr;
        Socket sockfd;
        EpollPoller poller;
    };
}

#endif //THREADPOOL_EPOLL_TCPSERVER_H
