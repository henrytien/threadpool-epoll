// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

#include "../../include/net/SocketIO.h"
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

namespace Henry {
    ssize_t SocketIO::readn(char *buf, size_t count) {
        size_t nleft = count;  // left bytes
        ssize_t nread;
        char *bufp = (char *) buf;
        while (nleft > 0) {
            nread = ::read(sockfd, bufp, nleft);
            if (nread == -1) {
                if (errno == EINTR) {
                    continue;
                }
                return -1;
            } else if (nread == 0) //EOF
            {
                break;
            }
            nleft -= nread;
            bufp += nread;
        }
        return (count - nleft);
    }

    ssize_t SocketIO::writen(const char *buf, size_t count) {
        size_t nleft = count;
        ssize_t nwrite;
        const char *bufp = buf;
        while (nleft > 0) {
            nwrite = ::write(sockfd, bufp, nleft);
            if (nwrite <= 0) {
                if (nwrite == -1 && errno == EINTR) {
                    continue;
                }
                return -1;
            }
            nleft -= nwrite;
            bufp += nwrite;
        }
        return count;
    }

    ssize_t SocketIO::recv_peek(char *buf, size_t len) {
        int nread;
        do {
            nread = ::recv(sockfd, buf, len, MSG_PEEK);
        } while (nread == -1 && errno == EINTR);
        return nread;
    }

    ssize_t SocketIO::readline(char *usrbuf, size_t maxlen) {
        size_t nleft = maxlen - 1;
        char *bufp = usrbuf;
        size_t total = 0;
        ssize_t nread = 0;
        while (nleft > 0) {
            nread = recv_peek(bufp,nleft);
            if(nread <= 0)
                return nread;

            //check \n
            for (int i = 0; i < nread; ++i) {
                if(bufp[i] == '\n')
                {
                    // find \n
                    size_t nsize = i +1;
                    if(readn(bufp,nsize) != static_cast<ssize_t>(nsize))
                        return -1;
                    bufp += nsize;
                    total += nsize;
                    *bufp = 0;
                    return total;
                }
            }

            //if not find \n
            if(readn(bufp,nread) != nread)
                return -1;
            bufp += nread;
            total += nread;
            nleft -= nread;
        }
        *bufp = 0;
        return maxlen - 1;
    }
}
