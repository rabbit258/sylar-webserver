#pragma once

#include "sylar/tcp_server.h"
#include "http_server.h"
#include "http_session.h"
#include "http_servlet.h"

namespace sylar{
namespace http{

class HttpServer : public TcpServer{
public :
    typedef std::shared_ptr<HttpServer> ptr;
    HttpServer(bool keepalive = false
                ,sylar::IOmanager* worker = sylar::IOmanager::GetThis()
                ,sylar::IOmanager* accept_worker = sylar::IOmanager::GetThis());

    ServletDispatch::ptr getServletDispatch() const {return m_dispatch;}
    void setServletDispatch(ServletDispatch::ptr v) {m_dispatch = v;}
protected:
    virtual void handleClient(Socket::ptr client) override;

private:
    bool m_isKeepalive;
    ServletDispatch::ptr m_dispatch;
};


}
}