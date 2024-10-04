#pragma once

#include "http.h"
#include "http11_parser.h"
#include "httpclient_parser.h"

#include "sylar/log.h"
#include "sylar/config.h"

namespace sylar{
namespace http{

class HttpRequestParser {
public:
    typedef std::shared_ptr<HttpRequestParser> ptr;
    HttpRequestParser();

    size_t execute(char * data,size_t len);
    int isFinished() ;
    int hasError() ; 

    HttpRequest::ptr getData() const {return m_data;}
    void setError(int v) {m_error = v;}

    uint64_t getContentLenth();

    static uint64_t GetHttpRequestBufferSize();
    static uint64_t GetHttpRequestMaxBodySize();
    // static uint64_t s_http_request_buffer_size = 0;
    // static uint64_t s_http_request_max_body_size = 0;
private:
    http_parser m_parser;
    HttpRequest::ptr m_data;
    //1000: invalid method
    //1001: invalid version
    //1002: invalid field
    int m_error;
};

class HttpResponseParser {
public:
    typedef std::shared_ptr<HttpResponseParser> ptr;
    HttpResponseParser();

    size_t execute(char * data,size_t len);
    int isFinished() ;
    int hasError() ; 
    void setError(int v) {m_error = v;}
    HttpResponse::ptr getData() const {return m_data;}
    uint64_t getContentLenth();
private:
    httpclient_parser m_parser;
    HttpResponse::ptr m_data;
    //1001: invalid version
    //1002: invalid field
    int m_error;
};


}
}