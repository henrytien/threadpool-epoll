// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#ifndef THREADPOOL_EPOLL_INETADDRESS_H
#define THREADPOOL_EPOLL_INETADDRESS_H

#include <string>
#include <netinet/in.h>
#define Error -1
using std::string;
namespace Henry
{
    class InetAddress{
    public:
        explicit InetAddress(unsigned short port);
        InetAddress(const string &ip, unsigned short port);
        InetAddress(const struct sockaddr_in &addr);

        void setSockAddrInet(const struct sockaddr_in &addr);
        const struct sockaddr_in *getSockAddrInet()const;
        string toIp()const;
        unsigned short toPort()const;

    private:
        struct sockaddr_in addr;
    };
}

#endif //THREADPOOL_EPOLL_INETADDRESS_H
