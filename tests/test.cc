#include <iostream>
#include "../kyubi/log.h"
#include "../kyubi/util.h"
int main(int argc,char** argv){
    #if 0
    std::cout<<"hello world" << std::endl;
    kyubi::Logger::ptr logger(new kyubi::Logger());
    logger->addAppender(kyubi::LogAppender::ptr(new kyubi::StdoutAppender));

    kyubi::FileAppedner::ptr file_appender(new kyubi::FileAppedner("./log.txt"));
    //file_appender->setLevel(kyubi::LogLevel::ERROR);
    //logger->addAppender(file_appender);
    kyubi::LogFormatter::ptr fmt(new kyubi::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    logger->addAppender(file_appender);
    std::cout << "hello kyubi"<<std::endl;
    //KYUBI_LOG_INFO(logger) << "test macro";
    //KYUBI_LOG_ERROR(logger) << "test macro error";
    #endif
    auto l = kyubi::LogMgr::GetInstance()->getLogger("xx");
    KYUBI_LOG_INFO(l) <<"xxx";
    return 0;
}