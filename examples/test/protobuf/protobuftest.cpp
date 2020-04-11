//
// Created by lsmg on 4/10/20.
//
#include <sys/time.h>
#include <Buffer.h>
#include <Logger.h>
#include "login.pb.h"
#include "protobuf/ProtobufCodec.h"

void OnMessage(const mongo::net::TcpConnectionPtr& conn, const mongo::net::MessagePtr& message)
{
    LOG_INFO << "On Login:\n" << message->GetTypeName() << '\n' << message->DebugString();
}

int main()
{
    struct timeval time;
    gettimeofday(&time, nullptr);
    mongo::LoginCS login_cs;

    login_cs.set_username("lsmg");
    login_cs.set_password("abc@123");
    login_cs.set_timestamp(time.tv_sec);

    mongo::net::Buffer buffer;
    mongo::net::ProtobufCodec codec_(OnMessage);

    codec_.SerializeToEmptyBuffer(&buffer, login_cs);

    size_t readable_bytes = buffer.ReadableBytes();

    printf("%ld\n", readable_bytes);

    for (int i = 0; i < readable_bytes; ++i)
    {
        printf("%02x ",*buffer.ReadBegin());;
        buffer.AddReadIndex(1);
    }

    // codec_.OnMessage(nullptr, &buffer);

}