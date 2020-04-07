//
// Created by lsmg on 4/7/20.
//

#ifndef MONGO_SRC_NET_TCPCONNECTION_H
#define MONGO_SRC_NET_TCPCONNECTION_H

#include <memory>
#include <noncopyable.h>
#include "ConnectionCallback.h"
#include "Buffer.h"
#include "InetAddress.h"

namespace mongo
{
namespace net
{
class EventLoop;
class Socket;
class Channel;

class TcpConnection : public noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop* loop, const std::string& name, int sockfd, const InetAddress& host_addr, const InetAddress& client_addr);
    ~TcpConnection();

    void Send(const char* msg, size_t len);

    void SetMessageCallback(const MessageCallback& cb)
    { message_callback_ = cb; }

    void SetWriteOverCallback(const WriteOverCallback& cb)
    { write_over_callback_ = cb; }

    void SetCloseCallback(const CloseCallback& cb)
    { close_callback_ = cb; }

    const std::string& GetConnectionName() const
    { return connection_name_; }

    const InetAddress& GetClientAddr() const
    { return client_addr_; }

    void ConnectionCreated();
private:

    enum Status{CONNECTING, CONNECTED, CLOSEING, CLOSED};

    EventLoop* loop_;
    std::string connection_name_;
    Status status_;

    Buffer input_buffer_;
    Buffer output_buffer_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

    const InetAddress host_addr_;
    const InetAddress client_addr_;

    MessageCallback message_callback_;

    // 发送未发送完的部分 归TCPConnection所管理, 发送完毕后可以触发回调
    WriteOverCallback write_over_callback_;
    CloseCallback close_callback_;

    void ReadHandle();
    void WriteHandle();
    void ErrorHandle();
    void CloseHandle();
};

}
}
#endif //MONGO_SRC_NET_TCPCONNECTION_H
