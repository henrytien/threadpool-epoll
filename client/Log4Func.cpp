//
// Created by henry on 1/18/2020.
//

#include "Log4Func.h"
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>

MyLog *MyLog::pInstance = NULL;

MyLog *MyLog::getInstance() {
    if (NULL == pInstance) {
        pInstance = new MyLog;
    }
    return pInstance;
}

void MyLog::destory() {
    if (pInstance) {
        Category::shutdown();
        delete pInstance;
    }
}

MyLog::MyLog() : cat(Category::getRoot().getInstance("mycat")) {
    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d:%c %p %x:%m%n");
    PatternLayout *ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d:%c %p %x:%m%n");

    OstreamAppender *osApp = new OstreamAppender("osApp", &cout);
    osApp->setLayout(ptn1);

    FileAppender *fileApp = new FileAppender("fileApp", "./Log/log4test.log");
    fileApp->setLayout(ptn2);

    cat.addAppender(osApp);
    cat.addAppender(fileApp);

    cat.setPriority(Priority::DEBUG);
}

MyLog::~MyLog() {}

void MyLog::warn(const string &msg) {
    cat.warn(msg);
}

void MyLog::info(const string &msg) {
    cat.info(msg);
}

void MyLog::error(const string &msg) {
    cat.error(msg);
}

void MyLog::debug(const string &msg) {
    cat.debug(msg);
}