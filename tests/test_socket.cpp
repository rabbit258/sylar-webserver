#include "sylar/socket.h"
#include "sylar/sylar.h"
#include "sylar/iomanager.h"


static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_sock(){
    auto addr = sylar::Address::LookupAnyIPaddress("ipv6.baidu.com");
    if(addr)
    {
        SYLAR_LOG_INFO(g_logger) << "get address :" << addr->toString();
    } else {
        SYLAR_LOG_INFO(g_logger) << "get address fail";
        return;
    }

    sylar::Socket::ptr sock = sylar::Socket::CreateTCPSocket();
    addr->setPort(80);
    if(!sock->connect(addr)){
        SYLAR_LOG_ERROR(g_logger) << "connect " << addr->toString() << " fail";
        return;
    }
    SYLAR_LOG_ERROR(g_logger) << "connect " << addr->toString() << " success";

    const char  buff[] = "GET / HTTP/1.0\r\n\r\n";
    int rt = sock->send(buff,sizeof(buff));
    if(rt <= 0){
        SYLAR_LOG_INFO(g_logger) << "send fail rt = " <<rt;
        return;
    }

    std::string buffs;
    buffs.resize(4096);
    rt = sock->recv(&buffs[0],buffs.size());

    if(rt <= 0){
        SYLAR_LOG_INFO(g_logger) << "recv fail rt = " <<rt;
        return;
    }

    buffs.resize(rt);
    SYLAR_LOG_INFO(g_logger) << buffs;
}

int main(int argc,char ** argv){
    sylar::IOmanager iom;
    iom.schedule(test_sock);
}