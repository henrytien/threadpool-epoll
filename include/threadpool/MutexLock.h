// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#ifndef THREADPOOL_EPOLL_MUTEXLOCK_H
#define THREADPOOL_EPOLL_MUTEXLOCK_H

#include "Noncopyable.h"
#include <pthread.h>
namespace Henry
{
    class MutexLock{
    public:
        MutexLock();
        ~MutexLock();
        void lock();
        void unlock();
        bool status() const;
        pthread_mutex_t *getMutexLockPtr();

    private:
        MutexLock(const MutexLock&);
        MutexLock&operator=(const MutexLock&);

    private:
        bool islocking;
        pthread_mutex_t mutex;
    };
}
#endif //THREADPOOL_EPOLL_MUTEXLOCK_H
