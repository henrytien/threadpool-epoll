// tianhangyu8886@gmail.com
// Created by Henry on 1/18/2020.

#include "./include/log/Log4Func.h"
#include "include/String2UpperServer.h"

int main(int argc,char *argv[])
{
    if(argc!= 2)
    {
        LogError("Please input my.conf path!");
        return -1;
    }

    std::cout<< argv[1] << std::endl;
    Henry::String2UpperServer query(argv[1]);
    query.start();
    return 0;

}
