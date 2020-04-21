//
// Created by lsmg on 4/10/20.
//

#include <EventLoop.h>
#include <protobuf/ProtobufServer.h>
#include <Logger.h>
#include "login.pb.h"

mongo::net::ProtobufServer* server_internal;

void OnUnknowMessage(const mongo::net::TcpConnectionPtr& conn, const mongo::net::MessagePtr& message)
{
    LOG_INFO << "On Unknow:\n" << message->GetTypeName() << '\n' << message->DebugString();
}

void OnLoginMessage(const mongo::net::TcpConnectionPtr& conn, const mongo::net::MessagePtr& message)
{
    LOG_INFO << "On Login:\n" << message->GetTypeName() << '\n' << message->DebugString();

    std::shared_ptr<mongo::LoginCS> login_cs = std::static_pointer_cast<mongo::LoginCS>(message);
    if (login_cs == nullptr)
    {
        LOG_WARN << "Invalid Login Message";
        return;
    }

    mongo::LoginSC login_sc;
    if (login_cs->username() != "123")
    {
        login_sc.set_result(mongo::USERNAME_NOT_EXIST);
    }
    else if (login_cs->password() != "456")
    {
        login_sc.set_result(mongo::PASSWORD_NOT_CORRECT);
    }
    else
    {
        login_sc.set_result(mongo::SUCCESS);
    }

    server_internal->Send(conn, &login_sc);
    conn->CloseConnection();
}


int main()
{
    mongo::net::EventLoop loop;
    mongo::net::InetAddress addr(8000);
    mongo::net::ProtobufServer server(&loop, "login-server", addr);
    server_internal = &server;

    server.SetUnknowMessageCallback(OnUnknowMessage);
    server.RegistCallback(mongo::LoginCS::descriptor(), OnLoginMessage);

    server.Start();
    loop.Loop();
}