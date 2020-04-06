//
// Created by lsmg on 4/6/20.
//

#ifndef MONGO_SRC_NET_INETADDRESS_H
#define MONGO_SRC_NET_INETADDRESS_H
#include <string>
#include <netinet/in.h>

namespace mongo
{
namespace net
{
class InetAddress
{
public:

    InetAddress();
    explicit InetAddress(short port);
    InetAddress(const std::string& ip, short port);
    ~InetAddress();

    const std::string& GetIpPort() const
    { return ip_port_; }

    const sockaddr_in& GetAddr() const
    { return addr_; }

    void SetAddr(sockaddr_in addr);
private:
    struct sockaddr_in addr_;
    std::string ip_port_;
};
}
}
#endif //MONGO_SRC_NET_INETADDRESS_H
