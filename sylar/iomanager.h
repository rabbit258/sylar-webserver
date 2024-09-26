#pragma once

#include "scheduler.h"

namespace sylar{
class IOmanager : public Scheduler{
public:
    typedef std::shared_ptr<IOmanager> ptr;
    typedef RWMutex RWMutexType;

    enum Event{
        NONE = 0x0,
        READ = 0x1,     //EPOLLIN
        WRITE = 0x4     //EPOLLOUT
    };

    IOmanager(size_t threads = 1,bool use_caller = true,const std::string & name = "");
    ~IOmanager();

    //1 success 0 retry -1 error
    int addEvent(int fd,Event event,std::function<void()> cb =nullptr);
    bool delEvent(int fd,Event event);
    bool cancelEvent(int fd,Event event);

    bool cancelALL(int fd);

    static IOmanager * GetThis();

protected:
    virtual void tickle() override;
    virtual bool stopping() override;
    virtual void idel() override;

    void contextResize(size_t size);
private:
    struct FdContext {
        typedef Mutex MutexType;
        struct EventContext{
            Scheduler * scheduler ;     //事件执行的scheduler
            Fiber::ptr fiber;           //事件协程
            std::function<void()> cb;   //事件的回调函数
        };

        EventContext & getContext(Event event);
        void resetContext(EventContext & ctx);
        void triggerEvent(Event event);

        int fd;                 //句柄
        EventContext read;      //读事件
        EventContext write;     //写事件
        Event m_events = NONE;  //已经注册的关联事件
        MutexType mutex;        
    };

    int m_epfd = 0;
    int m_tickleFds[2];

    std::atomic<size_t> m_pendingEventCount = {0};
    RWMutexType m_mutex;
    std::vector<FdContext *> m_fdContexts;
};
}