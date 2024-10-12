#pragma once

#include "scheduler.h"
#include "timer.h"

namespace sylar{
class IOmanager : public Scheduler,public TimerManager{
public:
    typedef std::shared_ptr<IOmanager> ptr;
    typedef RWMutex RWMutexType;

    //与epoll一致
    enum Event{
        NONE = 0x0,
        READ = 0x1,     //EPOLLIN
        WRITE = 0x4     //EPOLLOUT
    };
    //创建schduer，声明epoll，给fd添加监听事件用于唤醒线程
    IOmanager(size_t threads = 1,bool use_caller = true,const std::string & name = "");
    ~IOmanager();

    //1 success 0 retry -1 error
    //给fd添加一个event事件
    int addEvent(int fd,Event event,std::function<void()> cb =nullptr);
    //删除fd上的event事件，不会触发回调
    bool delEvent(int fd,Event event);
    //取消fd上的event事件，会触发回调
    bool cancelEvent(int fd,Event event);
    //取消fd上的所有事件
    bool cancelALL(int fd);

    static IOmanager * GetThis();

protected:
    void tickle() override;
    bool stopping() override;
    bool stopping(uint64_t & timeout);
    void idel() override;
    void onTimerInsertedAtFront() override;

    void contextResize(size_t size);
private:
    struct FdContext {
        typedef Mutex MutexType;
        struct EventContext{
            Scheduler * scheduler =nullptr ;     //事件执行的scheduler
            Fiber::ptr fiber;           //事件协程
            std::function<void()> cb;   //事件的回调函数
        };

        EventContext & getContext(Event event);
        void resetContext(EventContext & ctx);
        //触发事件，同时清空事件标记
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