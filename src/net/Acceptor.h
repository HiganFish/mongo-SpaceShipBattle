//
// Created by lsmg on 4/6/20.
//

#ifndef MONGO_SRC_NET_ACCEPTOR_H
#define MONGO_SRC_NET_ACCEPTOR_H

#include <memory>
#include "InetAddress.h"
#include "Socket.h"
#include "Channel.h"

namespace mongo
{
namespace net
{

class EventLoop;
class Acceptor : noncopyable
{
public:
    typedef std::function<void(int sockfd, const InetAddress& addr)> NewConnecionCallback;

    Acceptor(EventLoop* loop, const InetAddress& addr, bool reuse_port);
    ~Acceptor();

    void Listen();

    void HandleRead();

    void SetNewConnectionCallback(const NewConnecionCallback& callback)
    { newconnection_callback_ = callback; }
private:
    EventLoop* loop_;
    Socket listenfd_;
    Channel channel_;

    NewConnecionCallback newconnection_callback_;
};

}
}

#endif //MONGO_SRC_NET_ACCEPTOR_H
