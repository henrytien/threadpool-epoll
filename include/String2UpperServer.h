// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.



#ifndef THREADPOOL_EPOLL_STRING2UPPERSERVER_H
#define THREADPOOL_EPOLL_STRING2UPPERSERVER_H

#include "../include/net/TcpServer.h"
#include "../include/threadpool/ThreadPool.h"
#include "../include/net/TcpConnection.h"
#include "Configuration.h"
#include <memory>
namespace Henry{

    class String2UpperServer
            :public std::enable_shared_from_this<String2UpperServer>{
    public:
        String2UpperServer(const string &cfgFileName);
        void start();
        void onConnection(TcpConnectionPtr connectionPtr);
        void onMessage(TcpConnectionPtr connectionPtr);
        void onClose(TcpConnectionPtr connectionPtr);
        void doQuery(TcpConnectionPtr &connectionPtr, const string &query);

    private:
        Configuration conf;
        String2Upper wordQuery;
        ThreadPool threadPool;
        TcpServer tcpServer;
    };

}
#endif //THREADPOOL_EPOLL_STRING2UPPERSERVER_H
