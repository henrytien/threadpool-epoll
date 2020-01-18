// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.



#ifndef THREADPOOL_EPOLL_CONFIGURATION_H
#define THREADPOOL_EPOLL_CONFIGURATION_H

#include "FileName.h"
#include <set>
#include <iostream>
#include <map>

using std::map;
using std::set;
namespace Henry {
    class Configuration {
    public:
        Configuration(const string &filepath);

        void init();

        map<string, string> &getConfigMap();

        void debug();

    private:
        string filePath;
        map<string, string> configMap;
    };


    class String2Upper{
    public:
        String2Upper(Configuration &conf);
        string doQuery(const string &word);

    private:
        Configuration &conf;
    };
}

#endif //THREADPOOL_EPOLL_CONFIGURATION_H
