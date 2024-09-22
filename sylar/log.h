#pragma once

#include<string>
#include<stdint.h>
#include<memory>
#include<list>
#include<sstream>
#include<fstream>
#include<vector>
#include<stdarg.h>
#include<map>
#include"singleton.h"
#include"util.h"
#include"thread.h"

#define SYLAR_LOG_LEVEL(logger,level) \
    if(logger->getLevel() <= level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger,level,\
                            __FILE__,__LINE__,0,sylar::GetThreadId(),\
                            sylar::GetFiberId(),time(0),sylar::Thread::GetName()))).getSS()

#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::DEBUG)
#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::INFO)
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::WARN)
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::ERROR)
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::FATAL)

#define SYLAR_LOG_FMT_LEVEL(logger,level,fmt,...) \
    if(logger->getLevel()<=level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger,level,\
                            __FILE__,__LINE__,0,sylar::GetThreadId(),\
                            sylar::GetFiberId(),time(0),sylar::Thread::GetName()))).getEvent()->format(fmt,__VA_ARGS__)

#define SYLAR_LOG_FMT_DEBUG(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::DEBUG,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_INFO(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::INFO,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_WARN(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::WARN,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_ERROR(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::ERROR,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_FATAL(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::FATAL,fmt,__VA_ARGS__)

#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()
#define SYLAR_LOG_NAME(name) sylar::LoggerMgr::GetInstance()->getLogger(name)


namespace sylar {

class Logger;
class LoggerManager;

//日志级别
class LogLevel {
public: 
    enum Level {
        UNKNOW = 0,
        DEBUG = 1,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    static const char * Tostring(LogLevel::Level level);
    static LogLevel::Level FromString(const std::string & str);
};

//日志事件
class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger,LogLevel::Level level,const char * file , int32_t line , uint32_t elapse,
    uint32_t threadid,uint32_t fiberId,uint64_t time,const std::string & thread_name);

    const char * getFile() const {return m_file;}
    int32_t getLine() const {return m_line;}
    uint32_t getElapse() const {return m_elapse;}
    uint32_t getThreadId() const {return m_threadId;}
    uint32_t getFiberId() const {return m_fiberId;}
    uint64_t getTime() const {return m_time;}
    const std::string& getThreadName()const {return m_threadName;}
    std::string getContent() const {return m_ss.str();}
    std::stringstream & getSS() {return m_ss;}
    std::shared_ptr<Logger> getLogger() {return m_logger;}
    LogLevel::Level getLevel() {return m_level;}

    void format(const char * fmt,...);
    void format(const char * fmt,va_list al);
private:
    const char * m_file = nullptr; //文件名
    int32_t m_line = 0;            //行号
    uint32_t m_elapse = 0;         //程序启动毫秒数
    uint32_t m_threadId = 0;       //线程id
    uint32_t m_fiberId = 0;        //协程id
    uint64_t m_time =0;            //时间戳
    std::string m_threadName;
    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
    std::stringstream m_ss;
};

class LogEventWrap{
public:
    LogEventWrap(LogEvent::ptr event):m_event(event){};
    ~LogEventWrap();
    std::stringstream & getSS(){return m_event->getSS();}
    LogEvent::ptr getEvent(){return m_event;}
private:
    LogEvent::ptr m_event;
};

//日志格式器
class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string pattern);


    std::string format(std::shared_ptr<Logger>logger, LogLevel::Level level,LogEvent::ptr event);
// private:
    class FormatItem{
        public:
            typedef std::shared_ptr<FormatItem> ptr;
            // FormatItem(const std::string & fmt =""){}
            virtual ~FormatItem(){}
            virtual void format(std::ostream& os,std::shared_ptr<Logger>logger,LogLevel::Level level,LogEvent::ptr event) = 0;
    };

    void init();

    bool isError() const {return m_error;}
    std::string getPattern() const {return m_pattern;}
private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
    bool m_error =false;
};

//日志输出地
class LogAppender{
friend class Logger;
public:
    typedef std::shared_ptr<LogAppender> ptr;
    typedef Spinlock MutexType;
    virtual ~LogAppender(){};

    virtual void log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) = 0;
    
    virtual std::string toYamlString() = 0;

    void setFormatter(LogFormatter::ptr val);
    LogFormatter::ptr getFormatter();
    void setLevel(LogLevel::Level level){m_level=level;}
protected:
    LogLevel::Level m_level = LogLevel::DEBUG;
    bool m_hasFormatter = false;
    MutexType m_mutex;
    LogFormatter::ptr m_formatter;
};

//日志器
class Logger : public std::enable_shared_from_this<Logger>{
friend class LoggerManager;
public:
    typedef std::shared_ptr<Logger> ptr;
    typedef Spinlock MutexType;
    Logger(const std::string & name = "root");
    void log(LogLevel::Level level,LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);
    void error(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void clearAppenders();
    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level level){m_level = level;}

    const std::string & getName()const {return m_name;}

    void setFormatter(LogFormatter::ptr val);
    void setFormatter(const std::string & val);
    LogFormatter::ptr getFormatter();

    std::string toYamlString();
private:
    std::string m_name;      //日志名称
    LogLevel::Level m_level; //日志级别
    MutexType m_mutex;
    std::list<LogAppender::ptr> m_appender;        //Appender集合
    LogFormatter::ptr m_formatter;
    Logger::ptr m_root;
};

//输出到控制台的Appender
class StdoutLogAppender : public LogAppender {
public:
    virtual std::string toYamlString() override;
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    virtual void log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override;
};

//输出到文件的Appender
class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string filname);
    virtual void log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override;

    virtual std::string toYamlString() override;
    //重新开打文件
    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

class LoggerManager{
public:
    typedef Spinlock MutexType;
    LoggerManager();
    Logger::ptr getLogger(const std::string & name);

    void init();
    Logger::ptr getRoot()const {return m_root;}
    std::string toYamlString();
private:
    std::map<std::string,Logger::ptr> m_logger;
    Logger::ptr m_root;
    MutexType m_mutex;
};

typedef Singleton<LoggerManager> LoggerMgr;

}