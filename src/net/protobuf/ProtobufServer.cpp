//
// Created by lsmg on 4/10/20.
//

#include "ProtobufServer.h"

using namespace mongo;
using namespace mongo::net;

ProtobufServer::ProtobufServer(EventLoop* loop, const std::string& name, const InetAddress& addr):
server_(loop, name, addr),
dispatcher(UnknowProtobufMessageCallback),
codec_(std::bind(&Dispatcher::OnProtobufMessageCome, &dispatcher, _1, _2))

{
    server_.SetMessageCallback(std::bind(&ProtobufCodec::OnMessage, &codec_, std::placeholders::_1, std::placeholders::_2));
}
ProtobufServer::~ProtobufServer()
{

}
void ProtobufServer::SetThreadNum(int num)
{
    server_.SetThreadNum(num);
}
void ProtobufServer::UnknowProtobufMessageCallback(const TcpConnectionPtr& conn, const MessagePtr& message)
{

}
void ProtobufServer::Start()
{
    server_.Start();
}
