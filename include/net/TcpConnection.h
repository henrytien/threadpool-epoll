// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#ifndef THREADPOOL_EPOLL_TCPCONNECTION_H
#define THREADPOOL_EPOLL_TCPCONNECTION_H

#include "Socket.h"
#include "SocketIO.h"
#include "../threadpool/Noncopyable.h"
#include <memory>
#include <functional>

namespace Henry {
    class EpollPoller;

    class TcpConnection;

    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

    class TcpConnection : private Noncopyable, public std::enable_shared_from_this<TcpConnection> {
    public:
        typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;

        explicit TcpConnection(int sockfd, EpollPoller *p);

        ~TcpConnection();

        void setConnectCallback(TcpConnectionCallback cb) {
            onCloseCallback = std::move(cb);
        }

        void setMessageCallback(TcpConnectionCallback cb) {
            onMessageCallback = std::move(cb);
        }

        void setCloseCallback(TcpConnectionCallback cb) {
            onCloseCallback = std::move(cb);
        }

        void handleConnectCallback();

        void handleMessageCallback();

        void handleCloseCallback();

        void shutdown() {
            sockfd.shutdownWrite();
            isShutdownWrite = true;
        }

        ssize_t readn(char *buf, size_t count);

        ssize_t writen(const char *buf, size_t count);

        ssize_t readline(char *usrbuf, size_t maxlen);

        std::string receive();

        void send(const std::string &s);

        void sendInLoop(const std::string &s);



    private:
        Socket sockfd;
        SocketIO sockIO;
        const InetAddress localAddr;
        const InetAddress peerAddr;
        bool isShutdownWrite;

        EpollPoller *epollPoller;
        TcpConnectionCallback onConnectionCallback;
        TcpConnectionCallback onMessageCallback;
        TcpConnectionCallback onCloseCallback;
    };
}
#endif //THREADPOOL_EPOLL_TCPCONNECTION_H
