//
// Created by lsmg on 4/6/20.
//

#include <sys/socket.h>
#include <zconf.h>
#include "Socket.h"
#include "Log.h"
#include "InetAddress.h"

using namespace mongo;

net::Socket::Socket(int fd):
fd_(fd)
{

}
net::Socket::~Socket()
{
    close(fd_);
}

void net::Socket::SetReuseAddr(bool enable)
{
    int opt = enable ? 1 : 0;
    int ret = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, static_cast<void*>(&opt), static_cast<socklen_t>(sizeof opt));
    EXIT_IF(ret == -1, "%s reuseaddr error", enable ? "enable" : "disable");
}
void net::Socket::SetReusePort(bool enable)
{
    int opt = enable ? 1 : 0;
    int ret = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, static_cast<void*>(&opt), static_cast<socklen_t>(sizeof opt));
    EXIT_IF(ret == -1, "%s reuseport error", enable ? "enable" : "disable");
}

void net::Socket::Bind(const sockaddr_in& addr)
{
    int ret = bind(fd_, (sockaddr*)&addr, static_cast<socklen_t>(sizeof addr));
    EXIT_IF(ret == -1, "bind error")
}
void net::Socket::Listening()
{
    int ret = listen(fd_, SOMAXCONN);
    EXIT_IF(ret == -1, "listen error")
}
int net::Socket::Accept(InetAddress* addr)
{
    sockaddr_in address{};
    socklen_t socklen = static_cast<socklen_t>(sizeof address);
    int sockfd = accept(fd_, (sockaddr*)&address, &socklen);
    EXIT_IF(sockfd == -1, "accept error")
    addr->SetAddr(address);

    return sockfd;
}

int sockets::CreateNonBlockFd()
{
    int sockfd =  socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    EXIT_IF(sockfd < 0, "socket create error")
}
void sockets::SetNonblocking(int fd)
{

}
