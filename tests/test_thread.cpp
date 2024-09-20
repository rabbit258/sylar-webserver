#include"sylar/sylar.h"
#include <atomic>
sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();
// std::atomic<int> count(0);
long long count;
sylar::Mutex s_mutex;


void fun1(){

    SYLAR_LOG_INFO(g_logger)<<" name: "<<sylar::Thread::GetName()
                            <<" this.name: "<<sylar::Thread::GetThis()->getName()
                            <<" id: "<<sylar::GetThreadId()
                            <<" this.id: "<<sylar::Thread::GetThis()->getId();

    for(long long i =0;i<100000ll;++i){
        // sylar::Mutex::Lock lock(s_mutex);
        ++count;
    }
    SYLAR_LOG_INFO(g_logger) << "finish!";
}

void fun2(){
    while(true){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) <<"++++++++++++++++++++++++++++++++" ;
    }
}

void fun3(){
    while(true){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) <<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" ;
    }
}

int main(int argc,char ** argv){
    SYLAR_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("/home/fyx/sylar/bin/conf/log2.yaml");
    sylar::Config::LoadFromYaml(root);
    std::vector<sylar::Thread::ptr> thrs;
    srand(0);
    for(int i =0;i<1;++i){
        sylar::Thread::ptr thr(new sylar::Thread(&fun2,"name_"+std::to_string(i*2)));
        // sylar::Thread::ptr thr2(new sylar::Thread(&fun3,"name_"+std::to_string(i*2+1)));
        thrs.push_back(thr);
        // thrs.push_back(thr2);
    }


    for(size_t i=0;i<thrs.size();++i){
        thrs[i]->join();
    }

    SYLAR_LOG_INFO(g_logger) << count;
            

    return 0;
}