//
// Created by lsmg on 4/10/20.
//

#ifndef MONGO_SRC_NET_PROTOBUF_PROTOBUFSERVER_H
#define MONGO_SRC_NET_PROTOBUF_PROTOBUFSERVER_H

#include "TcpServer.h"
#include "ProtobufCodec.h"
#include "Dispatcher.h"

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

    void SetUnknowMessageCallback(const ProtobufMessageCallback& callback)
    {
        dispatcher.SetProtobufMessageCallback(callback);
    }

    void RegistCallback(const google::protobuf::Descriptor* descriptor, const ProtobufMessageCallback& callback)
    {
        dispatcher.RegistCallback(descriptor, callback);
    }

    void SetCloseCallback(const CloseCallback& callback);

    void SetNewConnectionCallback(const TcpServer::NewConnectionCallback& callback);

    void Start();

    void Send(const TcpConnectionPtr& conn, google::protobuf::Message* message);
private:
    TcpServer server_;
    Dispatcher dispatcher;
    ProtobufCodec codec_;

    static void UnknowProtobufMessageCallback(const TcpConnectionPtr& conn, const MessagePtr& message);
};
}
}

#endif //MONGO_SRC_NET_PROTOBUF_PROTOBUFSERVER_H
