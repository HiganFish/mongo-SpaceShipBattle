//
// Created by lsmg on 4/6/20.
//

#ifndef MONGO_SRC_NET_SOCKET_H
#define MONGO_SRC_NET_SOCKET_H

#include <netinet/in.h>
#include "noncopyable.h"
namespace mongo
{
namespace net
{
class InetAddress;
class Socket : noncopyable
{
public:
    explicit Socket(int fd);
    ~Socket();

    void SetReuseAddr(bool enable);
    void SetReusePort(bool enable);

    void SetKeepAlive(bool enable);

    void Bind(const sockaddr_in& addr);
    void Listening();

    int Accept(InetAddress* addr);

    int Send(const char* msg, size_t len);

    int GetFd() const
    { return sockfd_; }
private:
    int sockfd_;
};
}

namespace sockets
{
int CreateNonBlockFd();
void SetNonblocking(int fd);
}
}

#endif //MONGO_SRC_NET_SOCKET_H
