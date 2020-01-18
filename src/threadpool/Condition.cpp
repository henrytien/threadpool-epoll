// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.

#include "../../include/threadpool/Condition.h"
#include "../../include/threadpool/MutexLock.h"

namespace Henry
{
    Condition::Condition(MutexLock &mutexLock)
    :mutex(mutexLock){
        pthread_cond_init(&cond,NULL);
    }

    Condition::~Condition() {
        pthread_cond_destroy(&cond);
    }

    void Condition::wait() {
        pthread_cond_wait(&cond,mutex.getMutexLockPtr());
    }
    void Condition::notify()
    {
        pthread_cond_signal(&cond);
    }
    void Condition::notifyall() {
        pthread_cond_broadcast(&cond);
    }
}

