#include "sylar/http/http_server.h"
#include "sylar/log.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();
// sylar::IOmanager::ptr worker;
void run() {
    g_logger->setLevel(sylar::LogLevel::INFO);
    sylar::Address::ptr addr = sylar::Address::LookupAnyIPaddress("0.0.0.0:8020");
    if(!addr) {
        SYLAR_LOG_ERROR(g_logger) << "get address error";
        return;
    }

    sylar::http::HttpServer::ptr http_server(new sylar::http::HttpServer);
    // sylar::http::HttpServer::ptr http_server(new sylar::http::HttpServer(true));
    // bool ssl = false;
    while(!http_server->bind(addr)) {
        SYLAR_LOG_ERROR(g_logger) << "bind " << *addr << " fail";
        sleep(1);
    }

    // if(ssl) {
    //     //http_server->loadCertificates("/home/apps/soft/sylar/keys/server.crt", "/home/apps/soft/sylar/keys/server.key");
    // }

    http_server->start();
}

int main(int argc, char** argv) {
    sylar::IOmanager iom(32);
    // worker.reset(new sylar::IOmanager(4, false));
    iom.schedule(run);
    return 0;
}