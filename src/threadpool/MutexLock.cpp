// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.

#include "../../include/threadpool/MutexLock.h"

namespace Henry {
    MutexLock::MutexLock() :
            islocking(false) {
        pthread_mutex_init(&mutex, NULL);
    }

    MutexLock::~MutexLock() {
        pthread_mutex_destory(&mutex);
    }

    void MutexLock::lock() {
        pthread_mutex_lock(&mutex);
        islocking = true;
    }

    void MutexLock::unlock() {
        pthread_mutex_unlock(&mutex);
        islocking = false;
    }

    bool MutexLock::status() const {
        return islocking;
    }

    pthread_mutex_t * MutexLock::getMutexLockPtr()
    {
        return &mutex;
    }
}


