// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#include "Log4Func.h"
#include "../../include/net/TcpServer.h"

namespace Henry {
    int createSocketFd() {
        int fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (fd == Error) {
            LogError("create socket fd error!");
            exit(EXIT_FAILURE);
        }
        LogInfo("new fd: " + fd.tostring());
        return fd;
    }

    TcpServer::TcpServer(const string &ip, unsigned short port) :
            addr(ip, port), sockfd(createSocketFd()), poller(sockfd.fd()) {
        sockfd.setTcpNoDelay(false);
        sockfd.setReusePort(true);
        sockfd.setKeepAlive(false);
        sockfd.setReuseAddr(true);
        sockfd.bindAddress(addr);
        sockfd.listen();
    }

}