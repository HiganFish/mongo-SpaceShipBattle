//
// Created by lsmg on 4/10/20.
//

#include <EventLoop.h>
#include <protobuf/ProtobufServer.h>
#include <Logger.h>
#include "login.pb.h"

void OnUnknowMessage(const mongo::net::TcpConnectionPtr& conn, const mongo::net::MessagePtr& message)
{
    LOG_INFO << "On Unknow:\n" << message->GetTypeName() << '\n' << message->DebugString();
}

void OnLoginMessage(const mongo::net::TcpConnectionPtr& conn, const mongo::net::MessagePtr& message)
{
    LOG_INFO << "On Login:\n" << message->GetTypeName() << '\n' << message->DebugString();
}


int main()
{
    mongo::net::EventLoop loop;
    mongo::net::InetAddress addr(8000);
    mongo::net::ProtobufServer server(&loop, "protobuf_server", addr);

    server.SetUnknowMessageCallback(OnUnknowMessage);
    server.RegistCallback(mongo::LoginCS::GetDescriptor(), OnLoginMessage);

    server.Start();
    loop.Loop();
}