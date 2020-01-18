// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#include "../../include/log/Log4Func.h"
#include "../../include/net/EpollPoller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <sys/eventfd.h>

namespace {
    int createEpollFd() {
        int epollfd = ::epoll_create1(0);
        if (epollfd == Error) {
            LogError("create epoll fd error!");
            exit(EXIT_FAILURE);
        }
        return epollfd;
    }

    int createEventfd() {
        int fd = ::eventfd(0, 0);
        if (Error == fd) {
            LogError("Create event fd error!");
            exit(EXIT_FAILURE);
        }
        return fd;
    }

    void addEpollReadFd(int epollfd, int fd) {
        struct epoll_event ev;
        ev.data.fd = fd;
        ev.events = EPOLLIN;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == Error) {
            LogError("addEpollReadFd add epoll fd error!");
            exit(EXIT_FAILURE);
        }
    }

    void delEpollReadFd(int epollfd, int fd) {
        struct epoll_event ev;
        ev.data.fd = fd;
        if (epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev) == -1) {
            LogError("delEpollReadFd del epoll fd error!");
            exit(EXIT_FAILURE);
        }
    }

    int acceptConnFd(int listenfd) {
        int peerfd = ::accept(listenfd, NULL, NULL);
        if (peerfd == Error) {
            LogError("accept conn fd error!");
            exit(EXIT_FAILURE);
        }
        return peerfd;
    }

    ssize_t recvPeek(int sockfd, void *buf, size_t len) {
        int nread;
        do {
            nread = ::recv(sockfd, buf, len, MSG_PEEK);
        } while (nread == Error && errno == EINTR);
        return nread;
    }

    bool isConnectionClosed(int sockfd) {
        char buf[1024];
        ssize_t nread = recvPeek(sockfd, buf, sizeof(buf));
        if (nread == -1) {
            LogError("recvPeek error!");
            exit(EXIT_FAILURE);
        }
        return (nread == 0);
    }
}


namespace Henry {
    EpollPoller::EpollPoller(int listenfd) :
            epollfd(createEpollFd()),
            listenfd(listenfd),
            eventfd(createEventfd()),
            isLooping(false),
            activeEvents(1024) {
        addEpollReadFd(epollfd, listenfd);
        addEpollReadFd(epollfd, eventfd);
    }

    EpollPoller::~EpollPoller() {
        ::close(epollfd);
    }

    void EpollPoller::waitEpoollFd() {
        int nready = 0;
        do {
            nready = ::epoll_wait(epollfd, &(*activeEvents.begin()),
                                  static_cast<int>(activeEvents.size()), 5000);

        } while (nready == Error && errno == EINTR);

        if (nready == Error) {
            LogError("epoll wait error!");
            exit(EXIT_FAILURE);
        } else if (nready == 0) {
            //LogInfo("epoll timeout.");
        } else {
            // when vector full, allocate memory
            if (nready == static_cast<int>(activeEvents.size())) {
                activeEvents.resize(activeEvents.size() * 2);
            }
            // struct_event
            for (int i = 0; i != nready; ++i) {
                if (activeEvents[i].data.fd == listenfd) {
                    if (activeEvents[i].events & EPOLLIN) {
                        handleConnection();
                    } else if (activeEvents[i].data.fd == eventfd) {
                        handleRead();
                        doPendingFunctors();
                    } else {
                        if (activeEvents[i].events & EPOLLIN)
                            handleMessage(activeEvents[i].data.fd);
                    }
                }
            }
        }
    }

    // read eventfd
    void EpollPoller::handleRead() {
        uint64_t buff = 0;
        int ret = ::read(eventfd, &buff, sizeof(buff));
        if (ret != sizeof(buff)) {
            LogError("read eventfd error!");
        }
    }

    void EpollPoller::wakeup() {
        uint64_t one = 1;
        int ret = ::write(eventfd, &one, sizeof(one));
        if (ret != sizeof(one)) {
            LogError("read eventfd error!");
        }
    }

    void EpollPoller::runInLoop(Function func) {
        {
            MutexLockGuard guard(mutex);
            pendingFunctors.push_back(func);
        }
        wakeup();
    }

    void EpollPoller::doPendingFunctors() {
        std::cout << " doPendingFunctors()\n";
        std::vector<Function> tmp;
        {
            MutexLockGuard guard(mutex);
            tmp.swap(pendingFunctors);
        }

        for (auto &func:tmp) {
            LogInfo("func: ");
            if (func)
                func();
        }
    }

    void EpollPoller::handleConnection() {
        int peerfd = acceptConnFd(listenfd);

        addEpollReadFd(epollfd, peerfd);

        std::pair<ConnectionList::iterator, bool> ret;

        TcpConnectionPtr connectionPtr(new TcpConnection(peerfd, this));
        connectionPtr->setConnectCallback(onConnectCallback);
        connectionPtr->setMessageCallback(onMessageCallback);
        connectionPtr->setCloseCallback(onCloseCallback);

        ret = fd2ConnList.insert(std::make_pair(peerfd, connectionPtr));
        assert(ret.second == true);
        (void) ret;
        connectionPtr->handleConnectCallback();
    }

    void EpollPoller::handleMessage(int peerfd) {
        bool isClosed = isConnectionClosed(peerfd);
        ConnectionList::iterator iter = fd2ConnList.find(peerfd);

        assert(iter != fd2ConnList.end());
        if (isClosed) {
            iter->second->handleCloseCallback();
            delEpollReadFd(epollfd, peerfd);
            fd2ConnList.erase(iter);
        }
    }

    void EpollPoller::loop() {
        isLooping = true;
        while (isLooping) {
            waitEpoollFd();
        }
        LogInfo("Loop quit safely!");
    }

    void EpollPoller::unloop() {
        isLooping = false;
    }
}