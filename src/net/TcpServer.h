//
// Created by lsmg on 4/6/20.
//

#ifndef MONGO_SRC_NET_TCPSERVER_H
#define MONGO_SRC_NET_TCPSERVER_H

#include "Acceptor.h"

namespace mongo
{
namespace net
{
class TcpServer : noncopyable
{
public:
    TcpServer(EventLoop *loop, const InetAddress& addr);

    /**
     * start server listening
     */
    void Start();
private:

    EventLoop* loop_;
    std::unique_ptr<Acceptor> acceptor_;

    void NewConnection(int sockfd, const InetAddress& addr);
};
}
}
#endif //MONGO_SRC_NET_TCPSERVER_H
