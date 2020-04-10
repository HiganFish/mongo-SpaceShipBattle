//
// Created by lsmg on 4/10/20.
//

#ifndef MONGO_SRC_NET_PROTOBUF_PROTOBUFSERVER_H
#define MONGO_SRC_NET_PROTOBUF_PROTOBUFSERVER_H

#include "TcpServer.h"
#include "ProtobufCodec.h"
namespace mongo
{
namespace net
{
class ProtobufServer
{
public:
    typedef ProtobufCodec::ProtobufMessageCallback ProtobufMessageCallback;

    ProtobufServer(EventLoop* loop, const std::string& name, const InetAddress& addr);
    ~ProtobufServer();

    void SetThreadNum(int num);

    void SetProtobufMessageCallback(const ProtobufMessageCallback& callback)
    {
        codec_.SetProtobufMessageCallback(callback);
    }

    void Start();
private:
    TcpServer server_;
    ProtobufCodec codec_;

    static void DefaultProtobufMessageCallback(const TcpConnectionPtr& conn, const MessagePtr& message);
};
}
}

#endif //MONGO_SRC_NET_PROTOBUF_PROTOBUFSERVER_H
