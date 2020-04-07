//
// Created by lsmg on 4/6/20.
//
#include <EventLoop.h>
#include <TcpServer.h>

int main()
{
    mongo::net::EventLoop loop;
    mongo::net::InetAddress addr(8000);
    mongo::net::TcpServer server(&loop, "test", addr);
    server.Start();
    loop.Loop();
}