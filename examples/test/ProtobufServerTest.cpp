//
// Created by lsmg on 4/10/20.
//

#include <EventLoop.h>
#include <protobuf/ProtobufServer.h>

int main()
{
    mongo::net::EventLoop loop;
    mongo::net::InetAddress addr(8000);
    mongo::net::ProtobufServer server(&loop, "protobuf_server", addr);
    server.Start();
    loop.Loop();
}