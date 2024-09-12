#include "../sylar/log.h"
#include "../sylar/util.h"
#include<thread>
int main(int argc ,char ** argv)
{
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));
    // sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__,__LINE__,1,sylar::GetThreadId(),sylar::GetFiberId(),time(0)));
    // event->getSS()<<"rabbit";
    // logger->log(sylar::LogLevel::DEBUG,event);
    SYLAR_LOG_DEBUG(logger);
    return 0;
}