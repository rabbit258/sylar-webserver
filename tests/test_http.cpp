#include "sylar/http/http.h"
#include "sylar/log.h"

void test_req()
{
    sylar::http::HttpRequest::ptr req(new sylar::http::HttpRequest);
    req->setHeader("host","www.baidu.com");
    req->setBody("hello world");

    req->dump(std::cout);
}

void test_response() {
    sylar::http::HttpResponse::ptr rsp(new sylar::http::HttpResponse);
    rsp->setHeader("X-X","sylar");
    rsp->setBody("hello sylar");
    rsp->setStatus((sylar::http::HttpStatus)400);
    rsp->setClose(false);
    rsp->dump(std::cout);
}

int main(int argc,char ** argv){
    test_req();
    test_response();
    return 0;
}