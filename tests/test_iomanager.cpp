#include "sylar/sylar.h"
#include "sylar/iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_fiber(){
    SYLAR_LOG_INFO(g_logger) << "test_fiber";
}

void test1(){
    sylar::IOmanager iom(1,false);
    iom.schedule(&test_fiber);

    int fd = socket(AF_INET,SOCK_STREAM,0);
    fcntl(fd,F_SETFL,O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET,"180.101.50.188",&addr.sin_addr.s_addr);

    if(!connect(fd,(const sockaddr *)&addr,sizeof(addr))){
    } else if(errno == EINPROGRESS){
        SYLAR_LOG_INFO(g_logger) << "add event errno = " << errno << " "<< strerror(errno);
        sylar::IOmanager::GetThis()->addEvent(fd,sylar::IOmanager::READ,[](){
            SYLAR_LOG_INFO(g_logger) << "read callback";
        });
        sylar::IOmanager::GetThis()->addEvent(fd,sylar::IOmanager::WRITE,[=](){
            SYLAR_LOG_INFO(g_logger) << "write callback";
            sylar::IOmanager::GetThis()->cancelEvent(fd,sylar::IOmanager::READ);
            close(fd);
        });
    } else {
        SYLAR_LOG_INFO(g_logger) << "add event errno = " << errno << " "<< strerror(errno);
    }
}

int main(int argc,char ** argv){
    test1();
    return 0;
}