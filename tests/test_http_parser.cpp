#include "sylar/sylar.h"
#include "sylar/log.h"
#include "sylar/http/http_parser.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

const char test_request_data[] =    "GET / HTTP/1.1\r\n"
                                    "Host: www.baidu.com\r\n"
                                    "Content-Length: 10\r\n\r\n"
                                    "123456789";

void test_request(){
    sylar::http::HttpRequestParser parser;
    std::string tmp = test_request_data;
    size_t s =parser.execute(&tmp[0], tmp.size());
    SYLAR_LOG_INFO(g_logger) << "execute rt=" << s  
        << "has_error=" << parser.hasError()
        << " is_finished=" << parser.isFinished()
        << " total len = " << tmp.size()
        << " content_length=" << parser.getContentLenth();

    SYLAR_LOG_INFO(g_logger) << parser.getData()->toString();
}

const char test_response_data[] = 
"HTTP/1.0 200 OK\r\n"
"Accept-Ranges: bytes\r\n"
"Cache-Control: no-cache\r\n"
"Content-Length: 9508\r\n"
"Content-Type: text/html\r\n"
"Date: Wed, 02 Oct 2024 12:17:51 GMT\r\n"
"P3p: CP=\" OTI DSP COR IVA OUR IND COM \"\r\n"
"P3p: CP=\" OTI DSP COR IVA OUR IND COM \"\r\n"
"Pragma: no-cache\r\n"
"Server: BWS/1.1\r\n"
"Set-Cookie: BAIDUID=B6B4845A7FD70B7CF4025B0380D7ED48:FG=1; expires=Thu, 31-Dec-37 23:55:55 GMT; max-age=2147483647; path=/; domain=.baidu.com\r\n"
"Set-Cookie: BIDUPSID=B6B4845A7FD70B7CF4025B0380D7ED48; expires=Thu, 31-Dec-37 23:55:55 GMT; max-age=2147483647; path=/; domain=.baidu.com\r\n"
"Set-Cookie: PSTM=1727871471; expires=Thu, 31-Dec-37 23:55:55 GMT; max-age=2147483647; path=/; domain=.baidu.com\r\n"
"Set-Cookie: BAIDUID=B6B4845A7FD70B7C14A09875B5F7C060:FG=1; max-age=31536000; expires=Thu, 02-Oct-25 12:17:51 GMT; domain=.baidu.com; path=/; version=1; comment=bd\r\n"
"Traceid: 1727871471069086004210891204257854047192\r\n"
"Vary: Accept-Encoding\r\n"
"X-Ua-Compatible: IE=Edge,chrome=1\r\n"
"X-Xss-Protection: 1;mode=block\r\n\r\n"
"<!DOCTYPE html><html></html>\r\n";
void test_response(){
    sylar::http::HttpResponseParser parser;
    std::string tmp = test_response_data;
    size_t s = parser.execute(&tmp[0],tmp.size());
    SYLAR_LOG_INFO(g_logger) << "execute rt=" << s  
        << "has_error=" << parser.hasError()
        << " is_finished=" << parser.isFinished()
        << " total len = " << tmp.size()
        << " content_length=" << parser.getContentLenth();

    tmp.resize(tmp.size() - s);

    SYLAR_LOG_INFO(g_logger) << parser.getData()->toString();
    SYLAR_LOG_INFO(g_logger) << tmp;
}


int main(int argc,char ** argv){
    // test_request();
    test_response();
    return 0;
}