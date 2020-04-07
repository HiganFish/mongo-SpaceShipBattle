//
// Created by lsmg on 4/7/20.
//

#include <sys/socket.h>
#include "Buffer.h"

using namespace mongo;
using namespace mongo::net;

const int Buffer::DEFAULT_BUFFER_SIZE;
const int Buffer::BUFFER_BEGIN;


int Buffer::ReadFromFd(int sockfd)
{
    ssize_t ret = recv(sockfd, (void*)Begin(), WriteableBytes(), 0);
    if (ret > 0)
    {
        MoveWriteIndex(ret);
    }
    return ret;
}

void Buffer::SaveData(const char* begin, size_t len)
{
    if (len > WriteableBytes())
    {
        buffer_.resize(buffer_.size() + len - WriteableBytes());
    }
    std::copy(begin, begin + len, buffer_.begin() + write_index_);
    MoveWriteIndex(len);
}

Buffer::Buffer():
read_index_(BUFFER_BEGIN),
write_index_(BUFFER_BEGIN),
buffer_(DEFAULT_BUFFER_SIZE)
{

}
Buffer::~Buffer()
{

}
void Buffer::MoveReadIndex(size_t bytes)
{
    if (bytes < ReadableBytes())
    {
        read_index_ += bytes;
    }
    else
    {
        MoveReadIndexToEnd();
    }
}
void Buffer::MoveReadIndexToEnd()
{
    read_index_ = BUFFER_BEGIN;
    write_index_ = BUFFER_BEGIN;
}
void Buffer::MoveWriteIndex(size_t bytes)
{
    if (bytes <= WriteableBytes())
    {
        write_index_ += bytes;
    }
    else
    {
        write_index_ += WriteableBytes();
    }
}
std::string Buffer::ReadAllAsString()
{
    return ReadBytesAsString(ReadableBytes());
}
std::string Buffer::ReadBytesAsString(size_t bytes)
{
    if (bytes > ReadableBytes())
    {
        bytes = ReadableBytes();
    }
    std::string result(Begin(), bytes);
    MoveReadIndex(bytes);

    return result;
}
