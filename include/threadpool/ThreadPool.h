// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.



#ifndef THREADPOOL_EPOLL_THREADPOOL_H
#define THREADPOOL_EPOLL_THREADPOOL_H

#include "Buffer.h"
#include "Pthread.h"
#include <iostream>
#include <vector>
#include <memory>
#include <functional>

using std::vector;
using std::shared_ptr;

namespace Henry {
    class Thread;

    typedef std::function<void()> Task;

    class ThreadPool {
    public:
        ThreadPool(size_t threadNum, size_t buffsize);

        ~ThreadPool();

        void start();

        void stop();

        void addTask(Task task);

    private:
        Task getTask();

        void processTask();

    private:
        bool isExit;
        size_t threadNum;
        size_t bufSize;
        Buffer buffer;
        vector<shared_ptr<Thread>> threadList;
    };
}

#endif //THREADPOOL_EPOLL_THREADPOOL_H
