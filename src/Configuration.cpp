// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.
#include <fstream>
#include "../include/Configuration.h"
#include "../include/log/Log4Func.h"


namespace Henry
{
    Configuration::Configuration(const string &filepath):
    filePath(filepath){
        init();
    }

    void Configuration::init() {
        std::ifstream ifstream(filePath.c_str());
        if(!ifstream.good()){
            LogError("open file error!");
            ifstream.close();
            return;
        }

        string line;
        while (getline(ifstream,line))
        {
            std::istringstream stringstream(line);
            string key;
            string value;
            stringstream >> key >> value;
            configMap[key] = value;
        }
        ifstream.close();
    }

    map<string,string> &Configuration::getConfigMap() {
        return configMap;
    }
}

