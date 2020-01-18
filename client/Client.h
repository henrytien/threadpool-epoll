//
// Created by henry on 1/18/2020.
//

#ifndef THREADPOOL_EPOLL_CLIENT_H
#define THREADPOOL_EPOLL_CLIENT_H

#include "Log4Func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

#define ERR_EXIT(m) \
    do{ \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);

#define Error -1
#endif //THREADPOOL_EPOLL_CLIENT_H
