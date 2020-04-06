//
// Created by lsmg on 4/6/20.
//

#include "Log.h"
#include "TcpServer.h"

using namespace mongo;
using namespace mongo::net;

TcpServer::TcpServer(EventLoop* loop, const InetAddress& addr):
loop_(loop),
acceptor_(new Acceptor(loop, addr, true))
{

}

void TcpServer::Start()
{
    acceptor_->SetNewConnectionCallback(std::bind(&TcpServer::NewConnection, this, std::placeholders::_1, std::placeholders::_2));
    acceptor_->Listen();
}
void TcpServer::NewConnection(int sockfd, const InetAddress& addr)
{
    printf("new fd: %d, ip: %s\n", sockfd, addr.GetIpPort().c_str());
}
