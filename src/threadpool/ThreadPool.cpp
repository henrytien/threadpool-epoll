// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.

#include <unistd.h>
#include "../../include/threadpool/ThreadPool.h"
#include "../../include/log/Log4Func.h"

namespace Henry {
    ThreadPool::ThreadPool(size_t threadNum, size_t buffsize)
            : isExit(false), threadNum(threadNum), bufSize(buffsize), buffer(buffsize) {
        threadList.reserve(threadNum);
    }

    void ThreadPool::start() {
        for (int i = 0; i < threadNum; ++i) {
            shared_ptr<Thread> threadSharedPtr(new Thread(std::bind(&
                                                                            ThreadPool::processTask, this)));
            if (threadSharedPtr == NULL) {
                LogError("new threadSharedPtr fail!");
                return;
            }
            threadList.push_back(threadSharedPtr);
            threadSharedPtr->start();
        }
    }

    ThreadPool::~ThreadPool() {
        if (!isExit) {
            stop();
        }
    }

    void ThreadPool::stop() {
        if (!isExit) {
            //wait tasks finished
            while (!buffer.empty()) {
                sleep(1);
            }
            isExit = true; // tasks finished
            buffer.wakeup();
            for (auto &item:threadList) {
                item->join();
            }
        }
    }

    void ThreadPool::addTask(Task task) {
        buffer.push(task);
    }

    Task ThreadPool::getTask() {
        return buffer.pop();
    }

    void ThreadPool::processTask() {
        while (!isExit)
        {
            Task newTask = getTask();
            if(newTask)
            {
                newTask();
                LogInfo("newTask: ");
            }
        }
    }

}

