#include"log.h"

namespace sylar{
    Logger::Logger(const std::string &name): m_name(name)
    {
    }

    void Logger::log(LogLevel::Level level, LogEvent::ptr event)
    {
        if(level > m_level){
            for(auto & i : m_appender){
                i->log(level,event);
            }
        }
    }

    void Logger::debug(LogEvent::ptr event)
    {
        debug(LogLevel::DEBUG,event);
    }

    void Logger::info(LogEvent::ptr event)
    {
        debug(LogLevel::INFO,event);
    }

    void Logger::warn(LogEvent::ptr event)
    {
        debug(LogLevel::WARN,event);
    }

    void Logger::fatal(LogEvent::ptr event)
    {
        debug(LogLevel::FATAL,event);
    }
    void Logger::error(LogEvent::ptr event)
    {
        debug(LogLevel::ERROR,event);
    }
    void Logger::addAppender(LogAppender::ptr appender)
    {
        m_appender.push_back(appender);
    }
    void Logger::delAppender(LogAppender::ptr appender)
    {
        for(auto it = m_appender.begin();it!=m_appender.end();++it){
            if(*it == appender){
                m_appender.erase(it);
                break;
            }
        }
    }
    FileLogAppender::FileLogAppender(const std::string filname)
    {
    }
    void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event)
    {
        if(level>m_level){
            m_filestream << m_formatter.format(event);
        }
    }
    bool FileLogAppender::reopen()
    {
        if(m_filestream){
            m_filestream.close();
        }
        m_filestream.open(m_filename);
        return !!m_filestream;
    }
    void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event)
    {
        if(level>m_level){
            std::cout<< m_formatter.format(event);

        }
    }
    LogFormatter::LogFormatter(const std::string pattern):m_pattern(pattern)
    {
    }
    std::string LogFormatter::formate(LogEvent::ptr event)
    {
        std::stringstream ss;
        for(auto & i:m_items){
            i->format(ss,event);
        }
        return ss.str();
    }

    //%xxx %xxx{xxx} %%
    void LogFormatter::init()
    {
        //str,format,type
        std::vector<std::pair<std::string,std::string,int>> vec;
        std::string nstr;
        for(size_t i =0;i<m_pattern.size();++i){
            if(m_pattern[i]!='%'){
                nstr.append(1,m_pattern[i]);
                continue;
            }

            if((i+1)<m_pattern.size()){
                if(m_pattern[n+1]=='%'){
                    nstr.append(1,'%');
                    continue;
                }
            }

            size_t n= i +1;
            size_t fmt_begin = 0;
            int fmt_status = 0;

            std::string str;
            std::string fmt;
            while(n<m_pattern.size()){
                if(isspace(m_pattern[n])){
                    break;
                }
                if(fmt_status == 0){
                    if(m_pattern[n]=='{'){
                        str = m_pattern.substr(i+1,n-1);
                        fmt_status = 1;
                        ++n;
                        fmt_begin = n;
                        continue;
                    }
                }
                if(fmt_status == 1){
                    if(m_pattern[n]== '}'){
                        fmt = m_pattern.substr(fmt_begin+1 ,n-fmt_begin-1);
                        fmt_status = 2;
                        ++n;
                        continue;
                    }
                }
            }

            if(fmt_status == 0){
                if(!nstr.empty()){
                    vec.emplace_back(nstr,fmt,1);
                }
                str = m_pattern.substr(i+1,n-i-1);
                vec.emplace_back(str,fmt,1);
                i = n;
            }
            else if(fmt_status == 1){
                std::cout << "pattern parse error: "<< m_pattern <<" - "<< m_pattern.substr(1) << std::endl;
                vec.emplace_back("pattern_error",fmt,0);
            } 
            else if(fmt_status == 2){
                vec.emplace_back(str,fmt,1);
                i = n;
            }
        }
        if(!nstr.empty()){
            vec.emplace_back(nstr,"",0);
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
}