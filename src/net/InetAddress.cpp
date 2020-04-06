//
// Created by lsmg on 4/6/20.
//

#include <cstring>
#include <arpa/inet.h>
#include "InetAddress.h"

using namespace mongo;
using namespace mongo::net;

InetAddress::InetAddress():
addr_(),
ip_port_()
{

}

InetAddress::InetAddress(short port):
InetAddress("0.0.0.0", port)
{

}

InetAddress::InetAddress(const std::string& ip, short port)
{
    memset(&addr_, 0, sizeof addr_);
    ::inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr);
    addr_.sin_port = htons(port);
    addr_.sin_family = AF_INET;

    ip_port_ = ip + ":" + std::to_string(port);
}
InetAddress::~InetAddress()
{

}
void InetAddress::SetAddr(sockaddr_in addr)
{
    addr_ = addr;
    char buff[32];
    inet_ntop(AF_INET, &addr.sin_addr, buff, static_cast<socklen_t>(sizeof buff));
    int port = ntohs(addr.sin_port);

    ip_port_ = buff;
    ip_port_ += ":" + std::to_string(port);
}