// tianhangyu8886@gmail.com
// Created by henry on 1/18/2020.

//

#ifndef THREADPOOL_EPOLL_NONCOPYABLE_H
#define THREADPOOL_EPOLL_NONCOPYABLE_H
namespace Henry
{
    class Noncopyable{
    protected:
        Noncopyable(){}
        ~Noncopyable(){}
//        Noncopyable(const Noncopyable&) = delete;
//        Noncopyable& operator=(const Noncopyable&) = delete;
    private:
        Noncopyable(const Noncopyable &);
        Noncopyable &operator=(const Noncopyable &);
    };
}
#endif //THREADPOOL_EPOLL_NONCOPYABLE_H
