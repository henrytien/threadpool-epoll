// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.


#include "../include/Configuration.h"
#include "../include/String2UpperServer.h"
#include "../include/log/Log4Func.h"
#include <unistd.h>
#include <algorithm>
using std::bind;
namespace Henry {
    String2Upper::String2Upper(Configuration &conf) :
            conf(conf) {

    }
    typedef String2UpperServer str2UpServer;
    string String2Upper::doQuery(const string &word) {
        string ret = word;
        // All lower case to upper case
        transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
        return ret;
    }

    string absolutelyPath(const string &s) {
        char *cur = getcwd(NULL, 0);
        int locate = s.rfind('/');

        string path = s.substr(0, locate);
        chdir(path.c_str());
        string configAbsolutelyPath = getcwd(NULL, 0);
        configAbsolutelyPath.append("/").append(s.substr(locate + 1));
        chdir(cur);
        return configAbsolutelyPath;
    }

    void Trim(string &str) {
        str[str.size() - 1] = ' ';
        str.erase(str.find_last_not_of(' ') + 1);
        str.erase(0, str.find_first_not_of(' '));
        for (int i = 0; i < str.size(); ++i) {
            if(str[i] >='A' && str[i] <='Z')
                str[i] += 32;
        }
    }


    String2UpperServer::String2UpperServer(const string &cfgFileName) :
            conf(absolutelyPath(cfgFileName)), wordQuery(conf), threadPool(5, 10),
            tcpServer(conf.getConfigMap()[IP], atoi(conf.getConfigMap()[PORT].c_str())
            ) {

    }

    void String2UpperServer::start() {
        threadPool.start();
        tcpServer.setConnectCallback(bind(&str2UpServer::onConnection, this, std::placeholders::_1));
        tcpServer.setMessageCallback(bind(&str2UpServer::onMessage,this,std::placeholders::_1));
        tcpServer.setCloseCallback(bind(&str2UpServer::onClose,this,std::placeholders::_1));

        tcpServer.start();
    }

    void String2UpperServer::onConnection(TcpConnectionPtr connectionPtr) {
        LogInfo(connectionPtr->PrintInetAddressInfo() + ".");
        connectionPtr->send("hello, welcome to server!");
    }

    void String2UpperServer::onMessage(TcpConnectionPtr connectionPtr) {
        std::string queryWord(connectionPtr->receive());
        Trim(queryWord);

        threadPool.addTask(bind(&Henry::String2UpperServer::doQuery,this,connectionPtr,queryWord));
    }

    void String2UpperServer::onClose(TcpConnectionPtr connectionPtr) {
        LogInfo(connectionPtr->PrintInetAddressInfo()+ " close.");
    }

    void String2UpperServer::doQuery(TcpConnectionPtr &connectionPtr, const string &query) {
        string result = wordQuery.doQuery(query);
        connectionPtr->sendInLoop(result);
    }
}
