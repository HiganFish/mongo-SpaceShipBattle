//
// Created by lsmg on 4/10/20.
//

#include <Logger.h>
#include <zlib.h>
#include "ProtobufCodec.h"
using namespace mongo;
using namespace mongo::net;

const int ProtobufCodec::HEADER_LEN;
const int ProtobufCodec::MIN_MESSAGE_LEN;
const int ProtobufCodec::MAX_MESSAGE_LEN;

void ProtobufCodec::OnMessage(const TcpConnectionPtr& conn, Buffer* buffer)
{
    while (buffer->ReadableBytes() >= MIN_MESSAGE_LEN)
    {
        int32_t len = buffer->PeekInt32();
        if ((len < MIN_MESSAGE_LEN) || (len > MAX_MESSAGE_LEN))
        {
            invalid_message_callback_(conn, buffer, ErrorCode::INVALID_LENGTH);
            break;
        }
        else if (buffer->ReadableBytes() >= len + HEADER_LEN)
        {
            ErrorCode error = ErrorCode::NO_ERRROR;
            MessagePtr message =  Decode(buffer->ReadBegin() + HEADER_LEN, len, &error);
            if ((error == ErrorCode::NO_ERRROR) && message)
            {
                message_callback_(conn, message);
                buffer->AddReadIndex(len + HEADER_LEN);
            }
            else
            {
                invalid_message_callback_(conn, buffer, error);
                break;
            }
        }
        else
        {
            break;
        }

    }
}

const std::string ProtobufCodec::ErrorCodeToString[static_cast<int>(ProtobufCodec::ErrorCode::ERROR_LENGTH)]
{
    "NO_ERRROR",
    "INVALID_LENGTH",
    "INVALID_CHECKSUM",
    "INVALID_TYPE_LENGTH",
    "INVALID_PARSE",
    "INVALID_TYPE_NAME"
};

void ProtobufCodec::DefaultInvalidMessageCallback(const TcpConnectionPtr& conn, Buffer* buffer, ProtobufCodec::ErrorCode code)
{
    LOG_WARN << conn->GetConnectionName() << " DefaultInvalidMessageCallback: " << ErrorCodeToString[static_cast<int>(code)];

    if (conn && conn->Connected())
    {
        conn->CloseConnection();
    }
}
void ProtobufCodec::Send(const TcpConnectionPtr& conn, const MessagePtr& message)
{

}
MessagePtr ProtobufCodec::Decode(const char* buf, int32_t len, ErrorCode* error)
{
    MessagePtr message;

    int32_t message_sum = 0;
    ::memcpy(&message_sum, buf + len - HEADER_LEN, sizeof(int32_t));

    int32_t check_sum = static_cast<int32_t>(
        ::adler32(1,
            reinterpret_cast<const Bytef*>(buf),
            static_cast<int>(len - HEADER_LEN)));

    if (message_sum == check_sum)
    {
        int32_t typename_len = 0;
        ::memcpy(&typename_len, buf, HEADER_LEN);
        if ((typename_len <= len - 2 * HEADER_LEN) && (typename_len >= 2))
        {
            std::string type_name(buf + HEADER_LEN, buf + HEADER_LEN + typename_len);
            message = GetMessageByName(type_name);
            if (message)
            {
                const char* data = buf + HEADER_LEN + typename_len;
                int size = len - typename_len - 2 * HEADER_LEN;
                if (!message->ParseFromArray(data, size))
                {
                    *error = ErrorCode::INVALID_PARSE;
                }
            }
            else
            {
                *error = ErrorCode::INVALID_TYPE_NAME;
            }
        }
        else
        {
            *error = ErrorCode::INVALID_TYPE_LENGTH;
        }
    }
    else
    {
        *error = ErrorCode::INVALID_CHECKSUM;
    }
    return message;
}
MessagePtr ProtobufCodec::GetMessageByName(const std::string& type_name)
{
    MessagePtr message;
    const google::protobuf::Descriptor* descriptor =
        google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
    if (descriptor)
    {
        const google::protobuf::Message* proto_type =
            google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
        if (proto_type)
        {
            message.reset(proto_type->New());
        }
    }
    return message;
}

