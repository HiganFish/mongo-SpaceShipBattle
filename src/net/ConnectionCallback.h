//
// Created by lsmg on 4/7/20.
//

#ifndef MONGO_SRC_NET_CONNECTIONCALLBACK_H
#define MONGO_SRC_NET_CONNECTIONCALLBACK_H
#include <memory>
#include <functional>

namespace mongo
{
namespace net
{
class TcpConnection;
class Buffer;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

typedef std::function<void(const TcpConnectionPtr&)> WriteOverCallback;
typedef std::function<void(const TcpConnectionPtr&)> ErrorCallback;
typedef std::function<void(const TcpConnectionPtr&)> CloseCallback;

typedef std::function<void(const TcpConnectionPtr&, Buffer*)> MessageCallback;
}
}

#endif //MONGO_SRC_NET_CONNECTIONCALLBACK_H
