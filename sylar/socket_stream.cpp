#include "socket_stream.h"

namespace sylar{
SocketStream::SocketStream(Socket::ptr sock, bool owner)
    :m_socket(sock)
    ,m_owner(owner){
}
SocketStream::~SocketStream()
{
    if(m_owner&& m_socket){
        m_socket->close();
    }
}
int SocketStream::read(void *buff, size_t length)
{
    if(!isConnected()){
        return -1;
    }
    return m_socket->recv(buff,length);
}
int SocketStream::read(ByteArray::ptr ba, size_t length)
{
    if(!isConnected()){
        return -1;
    }
    std::vector<iovec> iovs;
    ba->getWriteBuffers(iovs,length);
    int rt = m_socket->recv(&iovs[0], iovs.size());
    if(rt > 0){
        ba->setPosition(ba->getPosition() + rt);
    }
    return rt;
}
int SocketStream::write(const void *buff, size_t length)
{
    if(!isConnected()){
        return -1;
    }
    return m_socket->send(buff,length);
}
int SocketStream::write(ByteArray::ptr ba, size_t length)
{
    if(!isConnected()){
        return -1;
    }
    std::vector<iovec> iovs;
    ba->getReadBuffers(iovs,length);
    int rt = m_socket->send(&iovs[0], iovs.size());
    if(rt > 0){
        ba->setPosition(ba->getPosition() + rt);
    }
    return rt;
}
void SocketStream::close()
{
    if(m_socket){
        m_socket->close();
    }
}
bool SocketStream::isConnected() const
{
    return m_socket && m_socket->isConnected();
}
}