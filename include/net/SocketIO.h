// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#ifndef THREADPOOL_EPOLL_SOCKETIO_H
#define THREADPOOL_EPOLL_SOCKETIO_H

#include "../threadpool/Noncopyable.h"
#include <sys/types.h>

namespace Henry {
    class SocketIO : Noncopyable {
    public:
        explicit SocketIO(int sockfd) : sockfd(sockfd) {}

        ssize_t readn(char *buf, size_t count);

        ssize_t writen(const char *buf, size_t count);

        ssize_t readline(char *usrbuf, size_t maxlen);

    private:
        ssize_t recv_peek(char *buf, size_t len);

        const int sockfd;
    };
}

#endif //THREADPOOL_EPOLL_SOCKETIO_H
