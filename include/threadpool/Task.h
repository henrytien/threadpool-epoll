// tianhangyu8886@gmail.com
// Created by Henry on 1/19/2020.



#ifndef THREADPOOL_EPOLL_TASK_H
#define THREADPOOL_EPOLL_TASK_H
namespace Henry
{
    class Task{
    public:
        virtual void execute()=0;
    };
}
#endif //THREADPOOL_EPOLL_TASK_H
