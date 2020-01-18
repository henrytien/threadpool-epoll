//
// Created by henry on 1/18/2020.
//

#ifndef THREADPOOL_EPOLL_LOG4FUNC_H
#define THREADPOOL_EPOLL_LOG4FUNC_H

#include <iostream>
#include <string>
#include <log4cpp/Category.hh>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;

class MyLog {
public:
    static MyLog *getInstance();

    static void destory();

    void warn(const string &msg);

    void error(const string &msg);

    void info(const string &msg);

    void debug(const string &msg);

private:
    MyLog();

    ~MyLog();

private:
    static MyLog *pInstance;
    Category &cat;
};

inline string int2str(int num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

#define  postfix(msg) \
    string(msg).append("[").append(__FILE__)\
                .append(":").append(__FUNCTION__)\
                .append(":").append(int2str(__LINE__)).append("]")

inline void logWarn(const string &msg) {
    MyLog *plog = MyLog::getInstance();
    plog->warn(msg);
}

inline void logInfo(const string &msg) {
    MyLog *plog = MyLog::getInstance();
    plog->info(msg);
}


inline void logError(const string &msg) {
    MyLog *plog = MyLog::getInstance();
    plog->error(msg);
}


inline void logDebug(const string &msg) {
    MyLog *plog = MyLog::getInstance();
    plog->debug(msg);
}


#define LogWarn(msg) logWarn(postfix(msg))
#define LogError(msg) logError(postfix(msg))
#define LogInfo(msg) logInfo(postfix(msg))
#define LogDebug(msg) logDebug(postfix(msg))

#endif //THREADPOOL_EPOLL_LOG4FUNC_H
