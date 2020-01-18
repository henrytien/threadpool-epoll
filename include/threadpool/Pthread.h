// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#ifndef THREADPOOL_EPOLL_PTHREAD_H
#define THREADPOOL_EPOLL_PTHREAD_H

#include "Noncopyable.h"
#include <functional>

using std::function;
namespace Henry
{
    class Thread:private Noncopyable{
        typedef function<void()> ThreadCallback;
    public:
        Thread(ThreadCallback cb);
        ~Thread();
        void start();
        void join();
        static void *threadFunc(void *arg);
        pthread_t getThreadId();

    private:
        pthread_t pthreadId;
        bool isRunning;
        ThreadCallback threadCb;

    };
}
#endif //THREADPOOL_EPOLL_PTHREAD_H
