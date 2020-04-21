//
// Created by lsmg on 4/6/20.
//

#include <Logger.h>
#include "TcpServer.h"
#include "TcpConnection.h"
#include "EventLoopThreadPoll.h"

using namespace mongo;
using namespace mongo::net;

TcpServer::TcpServer(EventLoop* loop, const std::string& name, const InetAddress& addr):
loop_(loop),
poll_(new EventLoopThreadPoll(loop_)),
server_name_(name),
acceptor_(new Acceptor(loop, addr, true)),
host_addr_(addr)
{
    message_callback_ = std::bind(&TcpServer::DefaultMessageCallback, this, std::placeholders::_1, std::placeholders::_2);
}

void TcpServer::Start()
{
    poll_->Start();
    acceptor_->SetNewConnectionCallback(std::bind(&TcpServer::NewConnection, this, std::placeholders::_1, std::placeholders::_2));
    acceptor_->Listen();
}
void TcpServer::NewConnection(int sockfd, const InetAddress& addr)
{
    std::string connection_name = server_name_ + "-" + addr.GetIpPort();

    /**
     * 这一行代码很妙, 单线程时候返回最初传入的事件循环 多线程返回对应的事件循环
     */
    EventLoop *io_loop = poll_->GetNextEventLoop();

    TcpConnectionPtr connection(new TcpConnection(io_loop, connection_name, sockfd, host_addr_, addr));
    connections[connection_name] = connection;
    connection->SetMessageCallback(message_callback_);
    connection->SetWriteOverCallback(writeover_callback_);
    connection->SetCloseCallback(std::bind(&TcpServer::CloseConnection, this, std::placeholders::_1));

    LOG_INFO << "connection " << connection_name << " connected";

    connection->ConnectionCreated();
    if (newconnection_callback_)
    {
        newconnection_callback_(connection);
    }
}
void TcpServer::CloseConnection(const TcpConnectionPtr& conn)
{
    connections.erase(conn->GetConnectionName());
    LOG_INFO << "connection " << conn->GetConnectionName() << " closed";

    if (close_callback_)
    {
        close_callback_(conn);
    }
}

void TcpServer::DefaultMessageCallback(const TcpConnectionPtr& conn, Buffer* buffer)
{
    std::string result = buffer->ReadAllAsString();

    LOG_INFO << server_name_.c_str() << " a new msg form " << conn->GetClientAddr().GetIpPort() << '\n' << result.c_str();
}
void TcpServer::SetThreadNum(int nums)
{
    poll_->SetThreadNums(nums);
}
