// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

#include "../../include/log/Log4Func.h"
#include "../../include/net/InetAddress.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace Henry {
    static_assert(sizeof(InetAddress) == sizeof(struct sockaddr_in), "InetAddress Error");

    InetAddress::InetAddress(unsigned short port) {
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);
    }

    InetAddress::InetAddress(const string &ip, unsigned short port) {
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        if (inet_aton(ip.c_str(), &addr.sin_addr) == 0) {
            LogError("ip invalid!");
            exit(EXIT_FAILURE);
        }
    }

    InetAddress::InetAddress(const struct sockaddr_in &addr) :
            addr(addr) {}

    string InetAddress::toIp() const {
        return inet_ntoa(addr.sin_addr);
    }

    unsigned short InetAddress::toPort() const {
        return ntohs(addr.sin_port);
    }

    const struct sockaddr_in * InetAddress::getSockAddrInet() const {
        return &addr;
    }

}

