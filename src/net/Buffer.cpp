//
// Created by lsmg on 4/7/20.
//

#include <sys/socket.h>
#include <sys/uio.h>
#include <cassert>
#include <cstring>
#include "Buffer.h"

using namespace mongo;
using namespace mongo::net;

const int Buffer::DEFAULT_BUFFER_SIZE;
const int Buffer::BUFFER_BEGIN;

Buffer::Buffer():
read_index_(BUFFER_BEGIN),
write_index_(BUFFER_BEGIN),
buffer_(DEFAULT_BUFFER_SIZE)
{

}
Buffer::~Buffer()
{

}

size_t Buffer::ReadFromFd(int fd)
{
    char exbuff[65535];
    struct iovec iovecs[2];

    const size_t writeable_size = WriteableBytes();

    iovecs[0].iov_base = static_cast<void*>(Begin() + write_index_);
    iovecs[0].iov_len = writeable_size;
    iovecs[1].iov_base = static_cast<void*>(exbuff);
    iovecs[1].iov_len = sizeof exbuff;

    int iov_count = writeable_size > sizeof exbuff ? 1 : 2;

    ssize_t ret = readv(fd, iovecs, iov_count);

    if (ret < 0)
    {
        return ret;
    }
    else if (ret < static_cast<ssize_t>(writeable_size))
    {
        write_index_ += ret;
    }
    else
    {
        write_index_ = buffer_.size();
        Append(exbuff, ret - writeable_size);
    }
    return ret;
}

void Buffer::AddReadIndex(size_t bytes)
{
    if (bytes < ReadableBytes())
    {
        read_index_ += bytes;
    }
    else
    {
        DropAllData();
    }
}
void Buffer::DropAllData()
{
    read_index_ = BUFFER_BEGIN;
    write_index_ = BUFFER_BEGIN;
}
void Buffer::AddWriteIndex(size_t bytes)
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
    std::string result(Begin() + read_index_, bytes);
    AddReadIndex(bytes);

    return result;
}

void Buffer::Append(const char* begin, size_t len)
{
    EnsureWriteBytes(len);
    std::copy(begin, begin + len, Begin() + write_index_);
    AddWriteIndex(len);
}
void Buffer::EnsureWriteBytes(size_t len)
{
    if (len > WriteableBytes())
    {
        ExpanseBuffer(len);
    }
    assert(len <= WriteableBytes());
}

void Buffer::ExpanseBuffer(size_t len)
{
    /**
     * 删除已读字节 剩余空间是否够存入新的数据
     */
    if (read_index_ - BUFFER_BEGIN > len)
    {
        size_t readable_bytes = ReadableBytes();
        std::copy(Begin() + read_index_, Begin() + write_index_, Begin() + BUFFER_BEGIN);
        write_index_ = readable_bytes + BUFFER_BEGIN;
        read_index_ = BUFFER_BEGIN;
        assert(readable_bytes == ReadableBytes());
    }
    else
    {
        buffer_.resize(write_index_ + len);
    }
}
int32_t Buffer::PeekInt32()
{
    if (ReadableBytes() >= sizeof(int32_t))
    {
        int32_t ret = 0;
        ::memcpy(&ret, ReadBegin(), sizeof(int32_t));
        return sockets::NetworkToHost32(ret);
    }
}
void Buffer::AppendInt32(int32_t num)
{
    int32_t network_num = sockets::HostToNetwork32(num);
    ::memcpy(WriteBegin(), &network_num, sizeof(num));
    AddWriteIndex(sizeof(num));
}
void Buffer::RAppendInt32(int32_t num)
{
    int32_t newwork_num = sockets::HostToNetwork32(num);
    size_t num_len = sizeof(newwork_num);
    assert(read_index_ <= BUFFER_BEGIN);
    assert(read_index_ >= num_len);
    memcpy(ReadBegin() - num_len, &newwork_num, num_len);
    read_index_ -= num_len;
}
