// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//
#include "../../include/net/TcpConnection.h"
#include "Log4Func.h"
#include "EpollPoller.h"
#include <cstring>

namespace Henry {
    TcpConnection::TcpConnection(int sockfd, EpollPoller *p)
            : sockfd(sockfd), sockIO(sockfd), localAddr(Socket::getLocalAddr(sockfd)),
              peerAddr(Socket::getPeerAddr(sockfd)), isShutdownWrite(false), epollPoller(p) {}

    TcpConnection::~TcpConnection() {
        if (!isShutdownWrite) {
            shutdown();
        }
    }

#if 1

    void TcpConnection::handleConnectCallback() {
        if (onConnectionCallback) {
            onConnectionCallback(shared_from_this());
        }
    }

    void TcpConnection::handleMessageCallback() {
        if (onMessageCallback) {
            onMessageCallback(shared_from_this());
        }
    }

    void TcpConnection::handleCloseCallback() {
        if (onCloseCallback) {
            onCloseCallback(shared_from_this());
        }
    }

#endif

    ssize_t TcpConnection::readn(char *buf, size_t count) {
        ssize_t ret = sockIO.readn(buf, count);
        if (ret == -1) {
            LogError("stderr TcpConnection::readn");
            exit(EXIT_FAILURE);
        }
        return ret;
    }

    ssize_t TcpConnection::writen(const char *buf, size_t count) {
        ssize_t ret = sockIO.writen(buf, count);
        if (ret == -1) {
            LogError("stderr TcpConnection writen!");
            exit(EXIT_FAILURE);
        }
        return ret;
    }

    ssize_t TcpConnection::readLine(char *usrbuf, size_t maxlen) {
        ssize_t ret = sockIO.readline(usrbuf, maxlen);
        if (ret == Error) {
            LogError("TcpConnection::readline error!");
            exit(EXIT_FAILURE);
        }
        return ret;
    }

    std::string TcpConnection::receive() {
        int size = 2 << 16 - 1;
        char str[size];
        memset(str,0,sizeof(str));
        int ret = readLine(str, sizeof(str));
        if (ret == 0)
            return std::string();
        else
            return std::string(str);
    }

    void TcpConnection::send(const std::string &s) {
        writen(s.c_str(), s.size());
    }

    void TcpConnection::sendInLoop(const std::string &s) {
        epollPoller->runInLoop(std::bind(&TcpConnection::send, shared_from_this(), s));
    }

    std::string TcpConnection::PrintInetAddressInfo() const
    {
        char text[100]={0};
        snprintf(text, sizeof(text),"%s:%d -> %s:%d",
        localAddr.toIp().c_str(),
        localAddr.toPort(),
        peerAddr.toIp(),
        peerAddr.toPort());
        return text;
    }
}
