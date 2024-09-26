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
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY,
        EXCEPT
    };
    Fiber(std::function<void()>cb,size_t stacksize = 0,bool use_caller = false);
    ~Fiber();
    void reset(std::function<void()> cb);
    void swapIn();
    void swapOut();
    void call();
    void back();
    uint64_t getId() const {return m_id;}
    State getState() const {return m_state;}
    static void SetThis(Fiber *f);
    static Fiber::ptr GetThis();
    static void YieldToReady();
    static void YieldToHold();
    
    static uint64_t TotalFibers();

    static void MainFunc();
    static void CallerMainFunc();
    static uint64_t GetFiberId();
private:
    Fiber();



    uint64_t m_id = 0;
    uint32_t m_stacksize = 0;
    State m_state = INIT;

    ucontext_t m_ctx;
    void * m_stack = nullptr;

    std::function<void()> m_cb;
};


}