#pragma once
#include<memory>
#include<list>
#include<vector>
#include<map>
#include"fiber.h"
#include"thread.h"


namespace sylar{
class Scheduler{

public:
    typedef std::shared_ptr<Scheduler> ptr;
    typedef Mutex MutexType;

    Scheduler(size_t threads = 1,bool use_caller = true,const std::string & name = "");
    virtual ~Scheduler();

    const std::string & getName() const {return m_name;}

    static Scheduler * GetThis();
    static Fiber* GetMainFiber();

    void start();
    void stop();

    template<class FiberOrCb>
    void schedule(FiberOrCb fc,int thread = -1){
        bool need_tickle = false;
        {
            MutexType::Lock lock(m_mutex);
            need_tickle = scheduleNoLock(fc,thread);
        }

        if(need_tickle){
            tickle();
        }
    }

    template<class InputIterator>
    void schedule(InputIterator begin,InputIterator end){
        bool need_tickle = false;
        {
            MutexType::Lock lock(m_mutex);
            while(begin!=end){
                need_tickle = scheduleNoLock(&*begin,-1) || need_tickle;
                ++begin;
            }
        }

        if(need_tickle){
            tickle();
        }
    }
protected:
    virtual void tickle();
    void run();
    virtual bool stopping();
    virtual void idel();
    void setThis();

    std::vector<int> m_threadIds;//线程池id
    size_t m_threadCount = 0;
    size_t m_activeThreadCount = 0;
    size_t m_idleThreadcount = 0;
    bool m_stopping = true;
    bool m_autoStop = false;
    bool hasIdleThreads() { return m_idleThreadcount > 0; }
    int m_rootThread = 0;
private:
struct FiberAndThread {
        Fiber::ptr fiber;
        std::function<void()> cb;
        int thread;

        FiberAndThread(Fiber::ptr f,int thr)
            :fiber(f),thread(thr){}

        FiberAndThread(Fiber::ptr * f,int thr)
            :thread(thr){
            fiber.swap(*f);
        }

        FiberAndThread(std::function<void()> f,int thr)
            :cb(f), thread(thr){

        }

        FiberAndThread(std::function<void()> * f,int thr)
            :thread(thr){
            cb.swap(*f);
        }

        FiberAndThread()
            :thread(-1){
        }   

        void reset(){
            fiber = nullptr;
            cb = nullptr;
            thread = -1;
        }     
};

    MutexType m_mutex;
    std::vector<Thread::ptr> m_threads;//线程池
    std::list<FiberAndThread> m_fibers;//任务池
    std::map<int,std::list<FiberAndThread>> m_thrFibers;//指定线程的任务
    std::string m_name;//调度器名字
    Fiber::ptr m_rootFiber;//主协程

    template<class FiberOrCb>
    bool scheduleNoLock(FiberOrCb fc,int thread){
        bool need_tickle = m_fibers.empty();
        FiberAndThread ft(fc,thread);
        if(ft.fiber || ft.cb){
            m_fibers.push_back(ft);
        }
        return need_tickle;
    }

    
};
}