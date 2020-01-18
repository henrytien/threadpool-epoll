// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.



#ifndef THREADPOOL_EPOLL_BUFFER_H
#define THREADPOOL_EPOLL_BUFFER_H

#include <functional>
#include "MutexLock.h"
#include "Condition.h"
#include <queue>

namespace Henry
{
    typedef std::function<void()> ElemType;

    class Buffer{
    public:
        Buffer(size_t size);
        void push(ElemType elem);
        ElemType pop();
        bool empty();
        bool full();
        void wakeup();

    private:
        MutexLock mutex;
        Condition notFull;
        Condition notEmpty;
        size_t size;
        bool flag;
        std::queue<ElemType> queue;
    };
}
#endif //THREADPOOL_EPOLL_BUFFER_H
