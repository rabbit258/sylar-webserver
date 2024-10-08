#include"log.h"
#include<map>
#include<functional>
#include<iostream>
#include"config.h"
#include"thread.h"

namespace sylar{
const char *LogLevel::Tostring(LogLevel::Level level)
{
    switch(level){
#define XX(name)  \
        case LogLevel::name: \
        return #name; 
        XX(DEBUG);
        XX(INFO);
        XX(WARN);
        XX(ERROR);
        XX(FATAL);
#undef XX
        default:
            return "UNKNOW"; 
    }
    return "UNKNOW"; 
}
LogLevel::Level LogLevel::FromString(const std::string &str)
{
#define XX(LEVEL,v) \
    if(str== #v){ \
        return LogLevel::LEVEL; \
    }
    XX(DEBUG,debug)
    XX(INFO,info)
    XX(WARN,warn)
    XX(ERROR,error)
    XX(FATAL,fatal)

    XX(DEBUG,DEBUG)
    XX(INFO,INFO)
    XX(WARN,WARN)
    XX(ERROR,ERROR)
    XX(FATAL,FATAL)
#undef XX
    return LogLevel::UNKNOW;
}
class MessageFormatItem : public LogFormatter::FormatItem
{
public:
    MessageFormatItem(const std::string &str = "") {}
    void format(std::ostream &os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override
    {
        os << event->getContent();
    }
};

class LevelFormatItem : public LogFormatter::FormatItem{
    public:
        LevelFormatItem(const std::string & str = ""){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << LogLevel::Tostring(level);
        }
};

class ElapseFormatItem : public LogFormatter::FormatItem{
    public:
        ElapseFormatItem(const std::string & str = ""){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << event->getElapse();
        }
};

class NameFormatItem : public LogFormatter::FormatItem{
    public:
        NameFormatItem(const std::string & str = ""){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << event->getLogger()->getName();
        }
};

class ThreadIdFormatItem : public LogFormatter::FormatItem{
    public:
        ThreadIdFormatItem(const std::string & str = ""){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << event->getThreadId();
        }
};

class FiberIdFormatItem : public LogFormatter::FormatItem{
    public:
        FiberIdFormatItem(const std::string & str = ""){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << event->getFiberId();
        }
};

class ThreadNameFormat : public LogFormatter::FormatItem{
    public:
        ThreadNameFormat(const std::string & str = ""){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << event->getThreadName();
        }
};

class DateTimeIdFormatItem : public LogFormatter::FormatItem{
    public:
        DateTimeIdFormatItem(const std::string & format = "%Y-%m-%d %H:%M:%S")
            :m_format(format){
                if(m_format.empty()){
                    m_format="%Y-%m-%d %H:%M:%S";
                }
            }
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            struct tm tm;
            time_t time = event->getTime();
            localtime_r(&time,&tm);
            char buf[64]={};
            strftime(buf,sizeof(buf),m_format.c_str(),&tm);
            os << buf;
        }
    private:
        std::string m_format;
};

class FilenameFormatItem : public LogFormatter::FormatItem{
    public:
        FilenameFormatItem(const std::string & str = ""){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << event->getFile();
        }
};

class LineFormatItem : public LogFormatter::FormatItem{
    public:
        LineFormatItem(const std::string & str = ""){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << event->getLine();
        }
};

class NewLineFormatItem : public LogFormatter::FormatItem{
    public:
        NewLineFormatItem(const std::string & str = ""){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << std::endl;
        }
};

class StringFormatItem : public LogFormatter::FormatItem{
    public:
        StringFormatItem(const std::string & str):
            m_string(str) {}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << m_string;
        }
    private:
        std::string m_string;
};

class TabFormatItem : public LogFormatter::FormatItem{
    public:
        TabFormatItem(const std::string & str){}
        void format(std::ostream& os,Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override{
            os << '\t';
        }
    private:
};

Logger::Logger(const std::string &name): m_name(name),m_level(LogLevel::DEBUG)
{
    m_formatter.reset(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));

}

void Logger::log(LogLevel::Level level, LogEvent::ptr event)
{
    if(level >= m_level){
        auto z = shared_from_this();
        MutexType::Lock lock(m_mutex);
        if(!m_appender.empty()){
            for(auto & i : m_appender){
                i->log(z,level,event);
            }
        }else if(m_root){
            m_root->log(level,event);
        }
    }
}

void Logger::debug(LogEvent::ptr event)
{
    log(LogLevel::DEBUG,event);
}

void Logger::info(LogEvent::ptr event)
{
    log(LogLevel::INFO,event);
}

void Logger::warn(LogEvent::ptr event)
{
    log(LogLevel::WARN,event);
}

void Logger::fatal(LogEvent::ptr event)
{
    log(LogLevel::FATAL,event);
}
void Logger::error(LogEvent::ptr event)
{
    log(LogLevel::ERROR,event);
}
void Logger::addAppender(LogAppender::ptr appender)
{
    MutexType::Lock lock(m_mutex);
    if(!appender->getFormatter()){
        MutexType::Lock lock(appender->m_mutex);
        appender->m_formatter=m_formatter;
    }
    m_appender.push_back(appender);
}
void Logger::delAppender(LogAppender::ptr appender)
{
    MutexType::Lock lock(m_mutex);
    for(auto it = m_appender.begin();it!=m_appender.end();++it){
        if(*it == appender){
            m_appender.erase(it);
            break;
        }
    }
}
void Logger::clearAppenders()
{
    MutexType::Lock lock(m_mutex);
    m_appender.clear();
}
void Logger::setFormatter(LogFormatter::ptr val)
{
    MutexType::Lock lock(m_mutex);
    m_formatter=val;

    for(auto & i :m_appender){
        MutexType::Lock ll(i->m_mutex);
        if(!i->m_hasFormatter){
            i->m_formatter=m_formatter;
        }
    }
}
void Logger::setFormatter(const std::string &val)
{
    sylar::LogFormatter::ptr new_val(new sylar::LogFormatter(val));
    if(new_val->isError()){
        std::cout<<"Logger setFormatter name=" <<m_name
                 <<"value = "<<val << "invalid formatter"
                 << std::endl;
        return;
    }
    // m_formatter=new_val;
    setFormatter(new_val);
}
LogFormatter::ptr Logger::getFormatter()
{
    MutexType::Lock lock(m_mutex);
    return m_formatter;
}
std::string Logger::toYamlString()
{
    MutexType::Lock lock(m_mutex);
    YAML::Node node;
    node["name"] = m_name;
    if(m_level != LogLevel::UNKNOW){
        node["level"] = LogLevel::Tostring(m_level);
    }
    if(m_formatter){
        node["formatter"] = m_formatter->getPattern();
    }

    for(auto & i: m_appender){
        node["appender"].push_back(YAML::Load(i->toYamlString()));
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}
FileLogAppender::FileLogAppender(const std::string filename) : m_filename(filename)
{
    reopen();
}
void FileLogAppender::log(std::shared_ptr<Logger>logger,LogLevel::Level level, LogEvent::ptr event)
{
    if(level>=m_level){
        MutexType::Lock lock(m_mutex);
        m_filestream << m_formatter->format(logger,level,event);
    }
}
std::string FileLogAppender::toYamlString()
{
    MutexType::Lock lock(m_mutex);
    YAML::Node node;
    node["type"] = "FileLogAppender";
    node["file"] = m_filename;
    if(m_level != LogLevel::UNKNOW){
        node["level"] = LogLevel::Tostring(m_level);
    }
    if(m_hasFormatter && m_formatter){
        node["formatter"] = m_formatter->getPattern();
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}
bool FileLogAppender::reopen()
{
    MutexType::Lock lock(m_mutex);
    if(m_filestream){
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return !!m_filestream;
}
std::string StdoutLogAppender::toYamlString()
{
    MutexType::Lock lock(m_mutex);
    YAML::Node node;
    node["type"] = "StdoutLogAppender";
    if(m_level != LogLevel::UNKNOW){
        node["level"] = LogLevel::Tostring(m_level);
    }
    if(m_hasFormatter&& m_formatter){
        node["formatter"] = m_formatter->getPattern();
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}
void StdoutLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{
    if(level>=m_level){
        MutexType::Lock lock(m_mutex);
        std::cout<< m_formatter->format(logger,level,event);

    }
}
LogFormatter::LogFormatter(const std::string pattern):m_pattern(pattern)
{
    init();
}
std::string LogFormatter::format(std::shared_ptr<Logger>logger,LogLevel::Level level,LogEvent::ptr event)
{
    std::stringstream ss;
    for(auto & i:m_items){
        i->format(ss,logger,level,event);
    }
    return ss.str();
}

//%xxx %xxx{xxx} %%
void LogFormatter::init()
{
    //str,format,type
    std::vector<std::tuple<std::string,std::string,int>> vec;
    std::string nstr;
    for(size_t i =0;i<m_pattern.size();++i){
        if(m_pattern[i]!='%'){
            nstr.append(1,m_pattern[i]);
            continue;
        }

        if((i+1)<m_pattern.size()){
            if(m_pattern[i+1]=='%'){
                nstr.append(1,'%');
                ++i;
                continue;
            }
        }

        size_t n= i +1;
        size_t fmt_begin = 0;
        int fmt_status = 0;

        std::string str;
        std::string fmt;
        while(n<m_pattern.size()){
            if(!fmt_status&&!isalpha(m_pattern[n])&&m_pattern[n]!='{'&&m_pattern[n]!='}'){
                break;
            }
            if(fmt_status == 0){
                if(m_pattern[n]=='{'){
                    str = m_pattern.substr(i+1,n-1-i);
                    fmt_status = 1;
                    ++n;
                    fmt_begin = n;
                    continue;
                }
            }
            if(fmt_status == 1){
                if(m_pattern[n]== '}'){
                    fmt = m_pattern.substr(fmt_begin ,n-fmt_begin);
                    fmt_status = 2;
                    ++n;
                    break;
                }
            }
            ++n;
        }

        if(fmt_status == 0){
            if(!nstr.empty()){
                vec.emplace_back(nstr,fmt,0);
                nstr.clear();
            }
            str = m_pattern.substr(i+1,n-i-1);
            vec.emplace_back(str,fmt,1);
            i = n - 1;
        }
        else if(fmt_status == 1){
            std::cout << "pattern parse error: "<< m_pattern <<" - "<< m_pattern.substr(1) << std::endl;
            m_error = true;
            vec.emplace_back("pattern_error",fmt,0);
        } 
        else if(fmt_status == 2){
            vec.emplace_back(str,fmt,1);
            i = n - 1;
        }
    }
    if(!nstr.empty()){
        vec.emplace_back(nstr,"",0);
        nstr.clear();
    }
    static std::map<std::string,std::function<FormatItem::ptr(const std::string & str)>> s_format_items = {
#define XX(str,C) \
        {#str,[](const std::string & fmt ){return FormatItem::ptr(new C(fmt));}}

        XX(m,MessageFormatItem),
        XX(p,LevelFormatItem),
        XX(r,ElapseFormatItem),
        XX(c,NameFormatItem),
        XX(t,ThreadIdFormatItem),
        XX(n,NewLineFormatItem),
        XX(d,DateTimeIdFormatItem),
        XX(f,FilenameFormatItem),
        XX(l,LineFormatItem),
        XX(T,TabFormatItem),
        XX(F,FiberIdFormatItem),
        XX(N,ThreadNameFormat)
#undef XX        
    };

    for(auto & i:vec){
        if(std::get<2>(i)==0){
            m_items.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
        } else {
            auto it = s_format_items.find(std::get<0>(i));
            if(it == s_format_items.end()){
                m_items.push_back(FormatItem::ptr(new StringFormatItem("<<error format %"+std::get<0>(i)+">>")));
                m_error = true;
            } else {
                m_items.push_back(it->second(std::get<1>(i)));
            }
        }

        // std::cout << std::get<0>(i) << " - "<<std::get<1>(i) << " - " << std::get<2>(i) <<std::endl;
    }
    //%m 消息体
    //%p level
    //%r 启动后时间
    //%c 日志名称
    //%t 线程id
    //%n 回车换行
    //%d 时间
    //%d 文件名
    //%l 行号


}

LogEvent::LogEvent(Logger::ptr logger,LogLevel::Level level,const char * file , int32_t line , uint32_t elapse,
    uint32_t threadid,uint32_t fiberId,uint64_t time,const std::string & thread_name)
    :m_file(file),m_line(line),m_elapse(elapse),m_threadId(threadid),m_fiberId(fiberId),
     m_time(time),m_threadName(thread_name),m_logger(logger),m_level(level)
{
}

LogEventWrap::~LogEventWrap()
{
    m_event->getLogger()->log(m_event->getLevel(),m_event);
}

void LogEvent::format(const char *fmt, ...)
{
    va_list al;
    va_start(al,fmt);
    format(fmt,al);
    va_end(al);
}

void LogEvent::format(const char *fmt, va_list al)
{
    char * buf = nullptr;
    int len = vasprintf(&buf,fmt,al);
    if(len!=-1){
        m_ss << std::string (buf,len);
        free(buf);
    }
}
LoggerManager::LoggerManager()
{
    m_root.reset(new Logger);

    m_root->addAppender(LogAppender::ptr(new StdoutLogAppender));

    m_logger[m_root->m_name] = m_root;

    init();
}
Logger::ptr LoggerManager::getLogger(const std::string &name)
{
    MutexType::Lock lock(m_mutex);
    auto it = m_logger.find(name);
    if(it != m_logger.end()){
        return it->second;
    }
    Logger::ptr logger(new Logger(name));
    logger->m_root = m_root;
    m_logger[name] = logger;
    return logger;
}

struct LogAppenderDefine{
    int type = 0;
    LogLevel::Level level = LogLevel::Level::UNKNOW;
    std::string formatter;
    std::string file;

    bool operator==(const LogAppenderDefine & oth)const {
        return type==oth.type&&
        level == oth.level&&
        formatter == oth.formatter&&
        file == oth.file;
    }
};
struct LogDefine {
    std::string name;
    LogLevel::Level level;
    std::string formatter;

    std::vector<LogAppenderDefine> appenders;

    bool operator==(const LogDefine& oth)const {
        return name == oth.name &&
        level == oth.level &&
        formatter == oth.formatter &&
        appenders == oth.appenders;
    }

    bool operator<(const LogDefine & oth) const{
        return name < oth.name ;
    }
};

template<>
class LexicalCast<std::string,std::set<LogDefine>> {
public:
    std::set<LogDefine> operator()(const std::string & v){
        YAML::Node node = YAML::Load(v);
        std::set<LogDefine> vec;
        for(size_t i = 0;i<node.size();++i){
            const auto & n =node[i];
            if(!n["name"].IsDefined()){
                std::cout<<"log config error: name is null ,"<<n <<std::endl;
                continue;
            }
            LogDefine id;
            id.name = n["name"].as<std::string>();
            id.level = LogLevel::FromString(n["level"].IsDefined()?n["level"].as<std::string>():"");
            if(n["formatter"].IsDefined()){
                id.formatter = n["formatter"].as<std::string>();
            }

            if(n["appender"].IsDefined()){
                for(size_t i= 0;i<n["appender"].size();++i){
                    auto a =n["appender"][i];
                    if(!a["type"].IsDefined()){
                        std::cout<<"log config error: appender type is null ,"<<a <<std::endl;
                        continue;
                    }
                    std::string type = a["type"].as<std::string>();
                    LogAppenderDefine lad;
                    if(type == "FileLogAppender"){
                        lad.type=1;
                        if(!a["file"].IsDefined()){
                            std::cout<<"log config error: fileappender file is null ,"<<a <<std::endl;
                            continue;
                        }
                        lad.file = a["file"].as<std::string>();
                        if(a["formatter"].IsDefined()){
                            lad.formatter = a["formatter"].as<std::string>();
                        }
                    }else if(type == "StdoutLogAppender"){
                        lad.type=2;
                    }else{
                        std::cout<<"log config error: appender type is invaild ,"<<a <<std::endl;
                        continue;
                    }
                    
                    id.appenders.push_back(lad);
                }
            }
            vec.insert(id);
        }
        return vec;
    }
};

template<>
class LexicalCast<std::set<LogDefine>,std::string> {
public:
    std::string operator()(const std::set<LogDefine> & v){
        YAML::Node node ;
        for(auto & i :v){
            YAML::Node n;
            n["name"] = i.name;
            if(i.level != LogLevel::UNKNOW){
                n["level"] =LogLevel::Tostring(i.level);
            }
            if(!i.formatter.empty()){
                n["formatter"]=i.formatter;
            }
            for(auto &a:i.appenders){
                YAML::Node na;
                if(a.type==1){
                    na["type"]="FileLogAppender";
                    na["file"]=a.file;
                }else if(a.type==2){
                    na["type"]="StdoutLogAppender";
                }
                if(a.level != LogLevel::UNKNOW){
                    na["level"] = LogLevel::Tostring(a.level);
                }
                na["level"] = LogLevel::Tostring(a.level);
                
                if(!a.formatter.empty()){
                    na["formatter"]=a.formatter;
                }

                n["appender"].push_back(na);
            }
            node.push_back(n);
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

ConfigVar<std::set<LogDefine>>::ptr g_log_defines = 
    Config::Lookup("logs",std::set<LogDefine>(),"logs config");

struct LogIniter{
    LogIniter(){
        g_log_defines->addListener([](const std::set<LogDefine> & old_value,
                    const std::set<LogDefine> & new_value){
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "on_logger_conf_changed";          
            for(auto & i :new_value){
                auto it = old_value.find(i);
                sylar::Logger::ptr logger;
                if(it==old_value.end()){
                    //add logger
                    logger = SYLAR_LOG_NAME(i.name);
                }else {
                    if(!(i == *it)){
                        //modify
                        logger = SYLAR_LOG_NAME(i.name);
                    }
                }
                logger->setLevel(i.level);
                if(!i.formatter.empty()){

                    logger->setFormatter(i.formatter);
                }

                logger->clearAppenders();
                for(auto & a:i.appenders){
                    sylar::LogAppender::ptr ap;
                    if(a.type==1){
                        ap.reset(new FileLogAppender(a.file));
                    }else if(a.type==2){
                        ap.reset(new StdoutLogAppender); 
                    }
                    ap->setLevel(a.level);
                    if(!a.formatter.empty()){
                        LogFormatter::ptr fmt(new LogFormatter(a.formatter));
                        if(!fmt->isError()){
                            ap->setFormatter(fmt);
                        }else {
                            std::cout << "appender type = "<<a.type << " format="<<
                            a.formatter << " is invalid" << std::endl;
                        }
                    }
                    logger->addAppender(ap);
                }
            }

            for(auto & i :old_value){
                auto it = new_value.find(i);
                if(it == new_value.end()){
                    //delete 
                    auto logger = SYLAR_LOG_NAME(i.name);
                    logger->setLevel((LogLevel::Level)100);
                    logger->clearAppenders();
                }
            }
        });
    }
};
static LogIniter __log_init;

void LoggerManager::init()
{

}
std::string LoggerManager::toYamlString()
{
    MutexType::Lock lock(m_mutex);
    YAML::Node node;
    for(auto & i : m_logger){
        node.push_back(YAML::Load(i.second->toYamlString()));
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}
void LogAppender::setFormatter(LogFormatter::ptr val)
{
    MutexType::Lock lock(m_mutex);
    m_formatter = val;
    if(m_formatter){
        m_hasFormatter = true;
    }
    else {
        m_hasFormatter = false;
    }
}
LogFormatter::ptr LogAppender::getFormatter()
{
    MutexType::Lock lock(m_mutex);
    return m_formatter;
}
}