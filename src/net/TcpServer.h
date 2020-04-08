//
// Created by lsmg on 4/6/20.
//

#ifndef MONGO_SRC_NET_TCPSERVER_H
#define MONGO_SRC_NET_TCPSERVER_H

#include <map>
#include "Acceptor.h"
#include "ConnectionCallback.h"

namespace mongo
{
namespace net
{

class EventLoopThreadPoll;

class TcpServer : noncopyable
{
public:
    TcpServer(EventLoop *loop, const std::string& name, const InetAddress& addr);

    /**
     * start server listening
     */
    void Start();

    void SetMessageCallback(const MessageCallback& cb)
    { message_callback_ = cb; }

    void SetWriteOverCallback(const WriteOverCallback& cb)
    { writeover_callback_ = cb; }

    void SetThreadNum(int nums);
private:

    EventLoop* loop_;
    std::shared_ptr<EventLoopThreadPoll> poll_;
    std::string server_name_;
    std::unique_ptr<Acceptor> acceptor_;
    const InetAddress host_addr_;

    MessageCallback message_callback_;
    WriteOverCallback writeover_callback_;

    typedef std::map<std::string, TcpConnectionPtr> ConnectionPtrMap;
    ConnectionPtrMap connections;

    void NewConnection(int sockfd, const InetAddress& addr);
    void CloseConnection(const TcpConnectionPtr& conn);
    void DefaultMessageCallback(const TcpConnectionPtr& conn, Buffer* buffer);
};
}
}
#endif //MONGO_SRC_NET_TCPSERVER_H
