// EpollPoller.h
// Created by henry on 1/18/2020.

//

#ifndef THREADPOOL_EPOLL_EPOLLPOLLER_H
#define THREADPOOL_EPOLL_EPOLLPOLLER_H

#include "../threadpool/Noncopyable.h"
#include "../threadpool/MutexLock.h"
#include "TcpConnection.h"
#include <vector>
#include <map>
#include <sys/epoll.h>
#include <functional>

namespace Henry {
    class EpollPoller : Noncopyable {
    public:
        typedef TcpConnection::TcpConnectionCallback EpollCallback;
        typedef std::function<void()> Function;

        explicit EpollPoller(int listenfd);

        ~EpollPoller();

        void loop(); //start
        void unloop(); //close epoll
        void setConnectCallback(EpollCallback cb) {
            onConnectCallback = std::move(cb);
        }

        void setMessageCallback(EpollCallback cb) {
            onMessageCallback = std::move(cb);
        }

        void setCloseCallback(EpollCallback cb) {
            onCloseCallback = std::move(cb);
        }

        void runInLoop(Function func);

    private:
        void waitEpoollFd();

        void handleConnection(); // handle accept
        void handleMessage(int peerfd); // handle msg

        void handleRead(); // handle eventfd
        void wakeup(); // wake up eventfd
        void doPendingFunctors(); // after wake up,execute callback

    private:
        const int epollfd;
        const int listenfd;
        const int eventfd;
        bool isLooping;

        MutexLock mutex;
        std::vector<Function> pendingFunctors;

        typedef std::vector<struct epoll_event> EventList;
        EventList activeEvents;
        typedef std::map<int, TcpConnectionPtr> ConnectionList;
        ConnectionList fd2ConnList;
        EpollCallback onConnectCallback;
        EpollCallback onMessageCallback;
        EpollCallback onCloseCallback;

    };

}


#endif //THREADPOOL_EPOLL_EPOLLPOLLER_H
