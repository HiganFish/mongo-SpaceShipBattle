//
// Created by lsmg on 4/10/20.
//

#ifndef MONGO_SRC_NET_PROTOBUF_DISPATCH_H
#define MONGO_SRC_NET_PROTOBUF_DISPATCH_H

#include <google/protobuf/message.h>
#include "ConnectionCallback.h"

namespace mongo
{
namespace net
{
class Dispatcher
{
public:
    typedef std::shared_ptr<google::protobuf::Message> MessagePtr;
    typedef std::function<void(const TcpConnectionPtr& conn, const MessagePtr& message)> ProtobufMessageCallback;

    explicit Dispatcher(const ProtobufMessageCallback& default_callback):
    default_callback_(default_callback)
    {

    }

    void OnProtobufMessageCome(const TcpConnectionPtr& conn, const MessagePtr& message)
    {
        CallbackMap::const_iterator iter =  callbacks_.find(message->GetDescriptor());

        if (iter != callbacks_.end())
        {
            iter->second(conn, message);
        }
        else
        {
            default_callback_(conn, message);
        }
    }

    void RegistCallback(const google::protobuf::Descriptor* descriptor, const ProtobufMessageCallback& callback)
    {
        if (descriptor)
        {
            callbacks_[descriptor] = callback;
        }
    }

    void SetProtobufMessageCallback(const ProtobufMessageCallback& callback)
    {
        default_callback_ = callback;
    }

private:
    ProtobufMessageCallback default_callback_;

    typedef std::map<const google::protobuf::Descriptor*, ProtobufMessageCallback> CallbackMap;
    CallbackMap callbacks_;
};
}
}
#endif //MONGO_SRC_NET_PROTOBUF_DISPATCH_H
