// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.

#include "../../include/threadpool/Pthread.h"
#include "../../include/log/Log4Func.h"
#include <iostream>

namespace Henry {
    Thread::Thread(ThreadCallback cb)
            : pthreadId(0),
              isRunning(false), threadCb(cb) {

    }

    void Thread::start() {
        pthread_create(&pthreadId, NULL, threadFunc, this);
        isRunning = true;
    }

    void Thread::join() {
        if (isRunning) {
            pthread_join(pthreadId, NULL);
            isRunning = false;
        }
    }

    void *Thread::threadFunc(void *arg) {
        Thread* pthread = static_cast<Thread*>(arg);
        if(pthread){
            pthread->threadCb;
        }
        return NULL;
    }
    Thread::~Thread() {
        LogInfo("Thread::~Thread().");
        if(isRunning){
            pthread_detach(pthreadId); //resource
            isRunning = false;
        }
    }
}


