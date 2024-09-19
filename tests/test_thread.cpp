#include"sylar/sylar.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();
long long count;
sylar::Mutex s_mutex;
void fun1(){

    SYLAR_LOG_INFO(g_logger)<<" name: "<<sylar::Thread::GetName()
                            <<" this.name: "<<sylar::Thread::GetThis()->getName()
                            <<" id: "<<sylar::GetThreadId()
                            <<" this.id: "<<sylar::Thread::GetThis()->getId();

    for(long long i =0;i<100000ll;++i){
        sylar::Mutex::Lock lock(s_mutex);
        count+=rand()%2;
    }
    SYLAR_LOG_INFO(g_logger) << "finish!";
}

void fun2(){

}

int main(int argc,char ** argv){
    SYLAR_LOG_INFO(g_logger) << "thread test begin";
    std::vector<sylar::Thread::ptr> thrs;
    srand(0);
    for(int i =0;i<5;++i){
        sylar::Thread::ptr thr(new sylar::Thread(&fun1,"name_"+std::to_string(i)));
        thrs.push_back(thr);
    }


    for(int i=0;i<5;++i){
        thrs[i]->join();
    }

    SYLAR_LOG_INFO(g_logger) << count;
            
    return 0;
}