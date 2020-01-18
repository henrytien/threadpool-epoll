// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.



#ifndef THREADPOOL_EPOLL_CONDITION_H
#define THREADPOOL_EPOLL_CONDITION_H

#include "Noncopyable.h"
#include <pthread.h>
namespace Henry {
    class MutexLock;

    class Condition : private Noncopyable {
    public:
        Condition(MutexLock &mutexLock);

        ~Condition();

        void wait();

        void notify();

        void notifyall();

    private:
        pthread_cond_t cond;
        MutexLock &mutex;
    };
}
#endif //THREADPOOL_EPOLL_CONDITION_H
