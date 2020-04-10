//
// Created by lsmg on 4/10/20.
//

#ifndef MONGO_SRC_NET_PROTOBUF_PROTOBUFCODEC_H
#define MONGO_SRC_NET_PROTOBUF_PROTOBUFCODEC_H

#include <google/protobuf/message.h>
#include <functional>
#include <utility>
#include "TcpConnection.h"
namespace mongo
{
namespace net
{

typedef std::shared_ptr<google::protobuf::Message> MessagePtr;

class ProtobufCodec : noncopyable
{
public:
    enum class ErrorCode
    {
        NO_ERRROR,
        INVALID_LENGTH,
        INVALID_CHECKSUM,
        INVALID_TYPE_LENGTH,
        INVALID_TYPE_NAME,
        INVALID_PARSE,
        ERROR_LENGTH
    };
    const static std::string ErrorCodeToString[static_cast<int>(ErrorCode::ERROR_LENGTH)];


    typedef std::function<void(const TcpConnectionPtr& conn, const MessagePtr& ptr)> ProtobufMessageCallback;
    typedef std::function<void(const TcpConnectionPtr& conn, Buffer* buffer, ErrorCode code)> InvalidMessageCallback;

    explicit ProtobufCodec(ProtobufMessageCallback  callback):
    message_callback_(std::move(callback)),
    invalid_message_callback_(DefaultInvalidMessageCallback)
    {}

    void OnMessage(const TcpConnectionPtr& conn, Buffer* buffer);

    void SerializeToEmptyBuffer(Buffer* buffer, const google::protobuf::Message& message);

    void Send(const TcpConnectionPtr& conn, const MessagePtr& message);

    void SetProtobufMessageCallback(const ProtobufMessageCallback& callback)
    {
        message_callback_ = callback;
    }
private:

//    struct Foo
//    {
//        int32_t len; >= 10   2 * 4+ namelen + data_len
//        int32_t namelen; >= 2
//        char type_name[namelen];
//        char protobuf_data[len - namelen - 8];
//        int32_t checksum; adler32
//    };

    const static int HEADER_LEN = sizeof(int32_t);
    const static int MIN_MESSAGE_LEN = 2 * HEADER_LEN + 2;
    const static int MAX_MESSAGE_LEN = 64 * 1024 * 1024;

    ProtobufMessageCallback message_callback_;
    InvalidMessageCallback invalid_message_callback_;

    static void DefaultInvalidMessageCallback(const TcpConnectionPtr& conn, Buffer* buffer, ErrorCode code);

    MessagePtr Decode(const char* buf, int32_t len, ErrorCode* error);

    MessagePtr GetMessageByName(const std::string& type_name);

    int32_t AsHostInt32(const char* buffer);
};
}
}
#endif //MONGO_SRC_NET_PROTOBUF_PROTOBUFCODEC_H
