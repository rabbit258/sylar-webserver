#include "../sylar/log.h"
#include "../sylar/util.h"
#include<thread>
int main(int argc ,char ** argv)
{
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));
    sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
    logger->addAppender(file_appender);
    // sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__,__LINE__,1,sylar::GetThreadId(),sylar::GetFiberId(),time(0)));
    // event->getSS()<<"rabbit";
    // logger->log(sylar::LogLevel::DEBUG,event);
    // SYLAR_LOG_DEBUG(logger);
    SYLAR_LOG_FMT_DEBUG(logger,"test %s","hello word");
    auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
    SYLAR_LOG_DEBUG(l)<<"ok?";
    return 0;
}