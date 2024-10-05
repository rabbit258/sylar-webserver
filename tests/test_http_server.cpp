#include "sylar/http/http_server.h"
#include "sylar/log.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run()
{
    sylar::http::HttpServer::ptr server(new sylar::http::HttpServer);
    sylar::Address::ptr addr = sylar::Address::LookupAnyIPaddress("0.0.0.0:80");
    while(!server->bind(addr)){
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/sylar/xx",[](sylar::http::HttpRequest::ptr req 
                                ,sylar::http::HttpResponse::ptr rsp
                                ,sylar::http::HttpSession::ptr session){
                rsp->setBody(req->toString());
                return 0;
        });

    sd->addGlobServlet("/sylar/*",[](sylar::http::HttpRequest::ptr req 
                                ,sylar::http::HttpResponse::ptr rsp
                                ,sylar::http::HttpSession::ptr session){
                rsp->setHeader("Content-Type","text/plain");
                rsp->setHeader("Transfer-Encoding","chunked");
                rsp->setBody(
                    "7\r\n"
                    "Mozilla\r\n"
                    "11\r\n"
                    "Developer Network\r\n"
                    "0\r\n"
                    "\r\n"
                );
                return 0;
        });
    
    server->start();
}

int main(int argc,char ** argv){
    sylar::IOmanager iom;
    iom.schedule(run);
    return 0;
}