#pragma once

#include<memory>
#include<set>
#include<vector>
#include "thread.h"

namespace sylar{
class TimerManager;
class Timer : public std::enable_shared_from_this<Timer> {
friend class TimerManager;
public:
    typedef std::shared_ptr<Timer> ptr;
    //取消该计时器
    bool cancel();
    //重置计时器
    bool refresh();
    //重置计时器周期，from_now 代表是否从现在开始
    bool reset(uint64_t ms, bool from_now);
private:
    Timer(uint64_t ms ,std::function<void()> cb,
        bool recurring ,TimerManager * manager);
    //辅助用
    Timer(uint64_t next);

    bool m_recurring = false;       //是否循环
    uint64_t m_ms;                  //执行周期
    uint64_t m_next;                //精确的执行时间 
    std::function<void()> m_cb;     //回调函数
    TimerManager * m_manager = nullptr;

    //排序用
    struct Comparator{
        bool operator()(const Timer::ptr & lhs,const Timer::ptr & rhs) const;
    };
};

class TimerManager {
friend class Timer;
public :
    typedef RWMutex RWMutexType;

    //记录一下当前时间
    TimerManager();
    virtual ~TimerManager();

    //添加一个计时器
    Timer::ptr addTimer(uint64_t ms, std::function<void()> cb
                        ,bool recurring = false);
    //添加条件计时器
    Timer::ptr addConditionTimer(uint64_t ms ,std::function<void()> cb
                                ,std::weak_ptr<void> weak_cond
                                ,bool recurring = false);
    uint64_t getNextTimer();
    void listExpiredCb(std::vector<std::function<void()>> & cbs);
    bool hasTimer();
protected:
    virtual void onTimerInsertedAtFront() = 0;
    void addTimer(Timer::ptr val , RWMutexType::WriteLock & lock);

private:
    bool detectClockRollover(uint64_t now_ms);

    RWMutexType m_mutex;
    std::set<Timer::ptr,Timer::Comparator> m_timers;
    bool m_tickled = false;
    uint64_t m_previousTime = 0;
};
}