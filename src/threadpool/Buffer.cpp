// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.

#include "../../include/threadpool/Buffer.h"
#include "../../include/threadpool/MutexLock.h"

namespace Henry {
    Buffer::Buffer(size_t size) :
            mutex(), notFull(mutex), notFull(mutex), size(size), flag(true) {}

    bool Buffer::full() {
        return queue.size() == size;
    }

    bool Buffer::empty() {
        return queue.size() == 0;
    }

    // producer thread
    void Buffer::push(ElemType elem) {
        // can't create temple variable, avoid deadlock in exception case
        MutexLockGuard guard(mutex);
        // here use while avoid condition wait in exception case
        while (full()) {
            notFull.wait();
        }
        queue.push(elem);
        notEmpty.notify();
    }

    // consumer thread
    ElemType Buffer::pop() {
        MutexLockGuard guard(mutex);
        while (flag && empty()) {
            notEmpty.wait();
        }
        if (flag) {
            ElemType ret = queue.front();
            queue.pop();
            notFull.notify();
            return ret;
        } else {
            return NULL;
        }
    }

    void Buffer::wakeup() {
        flag = false;
        notEmpty.notifyall();
    }
}
