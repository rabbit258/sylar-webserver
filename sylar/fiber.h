#pragma once
#include <ucontext.h>
#include <memory>
#include <functional>
// #include <thread.h>

namespace sylar{
class scheduler;
class Fiber : public std::enable_shared_from_this<Fiber> {
friend class Scheduler;
public :
    typedef std::shared_ptr<Fiber> ptr;


    enum State {
        /// 初始化状态
        INIT,
        /// 暂停状态
        HOLD,
        /// 执行中状态
        EXEC,
        /// 结束状态
        TERM,
        /// 可执行状态
        READY,
        /// 异常状态
        EXCEPT
    };
    /**
     * @brief 构造函数
     * @param[in] cb 协程执行的函数
     * @param[in] stacksize 协程栈大小
     * @param[in] use_caller 是否在MainFiber上调度
     */
    Fiber(std::function<void()>cb,size_t stacksize = 0,bool use_caller = false);
    ~Fiber();
    void reset(std::function<void()> cb);
    //执行该协程
    void swapIn();
    //让出协程
    void swapOut();
    //将当前协程切换到执行状态，该函数的调用协程为主协程
    void call();
    //返回到主协程
    void back();

    uint64_t getId() const {return m_id;}
    State getState() const {return m_state;}
    static void SetThis(Fiber *f);
    static Fiber::ptr GetThis();
    //将当前协程切换到后台,并设置为READY状态
    static void YieldToReady();
    //将当前协程切换到后台,并设置为HOLD状态
    static void YieldToHold();
    
    static uint64_t TotalFibers();

    //协程执行函数,执行完后回到主协程
    static void MainFunc();
    //协程执行函数,执行完后回到调度协程
    static void CallerMainFunc();
    static uint64_t GetFiberId();
private:
    //每个线程第一个协程的构造
    Fiber();



    uint64_t m_id = 0;
    uint32_t m_stacksize = 0;
    State m_state = INIT;

    ucontext_t m_ctx;
    void * m_stack = nullptr;

    std::function<void()> m_cb;
};


}