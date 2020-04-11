//
// Created by lsmg on 4/6/20.
//

#include <Logger.h>
#include "Acceptor.h"

using namespace mongo;
using namespace mongo::net;

Acceptor::Acceptor(EventLoop* loop, const InetAddress& addr, bool reuse_port):
loop_(loop),
listenfd_(sockets::CreateNonBlockFd()),
channel_(loop, listenfd_.GetFd())
{
    listenfd_.SetReuseAddr(true);
    listenfd_.SetReusePort(reuse_port);
    listenfd_.Bind(addr.GetAddr());
    LOG_INFO << "Bind on " << addr.GetIpPort();
}
Acceptor::~Acceptor()
{

}
void Acceptor::Listen()
{
    listenfd_.Listening();
    channel_.SetReadCallback(std::bind(&Acceptor::HandleRead, this));
    channel_.EnableReading();
}
void Acceptor::HandleRead()
{
    InetAddress addr;
    int fd = listenfd_.Accept(&addr);

    if (newconnection_callback_)
    {
        newconnection_callback_(fd, addr);
    }
}
