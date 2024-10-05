#include <iostream>
#include "sylar/http/http_connection.h"
#include "sylar/log.h"
#include "sylar/iomanager.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_pool(){
    sylar::http::HttpConnectionPool::ptr pool(new sylar::http::HttpConnectionPool(
                        "www.baidu.com" ,"",80,10,1000 * 30,5
    ));
    sylar::IOmanager::GetThis()->addTimer(1000, [pool](){
        auto r =pool->doGet("/",300);
        SYLAR_LOG_INFO(g_logger) << r->toString();
    }, true);
}

void run(){
    sylar::Address::ptr addr = sylar::Address::LookupAnyIPaddress("180.101.50.188:80");
    if(!addr){
        SYLAR_LOG_INFO(g_logger) << "get addr error";
        return;
    }

    sylar::Socket::ptr sock = sylar::Socket::CreateTCPSocket(addr);
    bool rt = sock->connect(addr);
    if(!rt) {
        SYLAR_LOG_INFO(g_logger) << "connect " << *addr << " failed";
        return;
    }

    sylar::http::HttpConnection::ptr conn(new sylar::http::HttpConnection(sock));
    sylar::http::HttpRequest::ptr req(new sylar::http::HttpRequest);
    req->setPath("/sylar/x");
    req->setHeader("host","0.0.0.0");
    SYLAR_LOG_INFO(g_logger) << "req:" <<std::endl 
        << *req;

    conn->sendRequest(req);
    auto rsp = conn->recvResponse();

    if(!rsp) {
        SYLAR_LOG_INFO(g_logger) << "recv response error";
        return;
    }
    SYLAR_LOG_INFO(g_logger) << "rsp:" <<std::endl  << *rsp;

    SYLAR_LOG_INFO(g_logger) << "===========================";

    auto r =sylar::http::HttpConnection::DoGet("http://www.baidu.com/",300);
    SYLAR_LOG_INFO(g_logger) << "result = " <<r->result
            << " error = " << r->error
            << " rsp = " << (r->response? r->response->toString() : "");
    SYLAR_LOG_INFO(g_logger) << "===========================";
    test_pool();
}

int main(int argc,char * * argv){
    sylar::IOmanager iom;
    iom.schedule(run);
    return 0;
}