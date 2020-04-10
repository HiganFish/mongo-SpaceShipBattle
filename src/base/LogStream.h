//
// Created by lsmg on 4/9/20.
//

// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MONGO_SRC_BASE_LOGSTREAM_H
#define MONGO_SRC_BASE_LOGSTREAM_H

#include <cstddef>
#include <type_traits>
#include <cassert>
#include <cstring>
#include <string>
#include <cstdio>
#include "noncopyable.h"
namespace mongo
{
class LogBuffer : noncopyable
{
public:
    LogBuffer():
    cur_(buffer_){}

    size_t Length() const
    {
        return cur_ - buffer_;
    }

    const char* GetData() const
    {
        return buffer_;
    }

    size_t WriteableBytes() const
    {
        return BUFFER_SIZE - (cur_ - buffer_);
    }

    void Append(const char* data, size_t len)
    {
        if (WriteableBytes() > len)
        {
            memcpy(cur_, data, len);
            cur_ += len;
        }
    }

    char* WritePoint() const
    {
        return cur_;
    }

    void MoveWritePoint(size_t t)
    {
        cur_ += t;
    }
private:
    const static int BUFFER_SIZE = 4096;
    char buffer_[BUFFER_SIZE];
    char* cur_;
};

class LogStream
{
public:

    LogStream& Append(const char* str, size_t len)
    {
        buffer_.Append(str, len);
        return *this;
    }

    LogStream& operator<<(short num);
    LogStream& operator<<(unsigned short num);
    LogStream& operator<<(int num);
    LogStream& operator<<(unsigned num);
    LogStream& operator<<(long num);
    LogStream& operator<<(unsigned long num);
    LogStream& operator<<(long long num);
    LogStream& operator<<(unsigned long long num);

    LogStream& operator<<(char str);
    LogStream& operator<<(const char* str);
    LogStream& operator<<(const std::string& str);

    const LogBuffer& GetBuffer() const
    {
        return buffer_;
    }
private:
    LogBuffer buffer_;

    template<typename T>
    void FormatInteger(T t);

    static const int MAX_NUMBER_SIZE = 32;
};

class Fmt
{
public:
    template<typename T>
    Fmt(const char* fmt, T val);

    const char* GetData() const
    {
        return buff_;
    }
    int GetLength() const
    {
        return length_;
    }

private:
    char buff_[32];
    size_t length_;
};

template<typename T>
Fmt::Fmt(const char* fmt, T val)
{
    static_assert(std::is_arithmetic<T>::value == true, "Must be arithmetic type");
    length_ = snprintf(buff_, sizeof buff_, fmt, val);
    assert(length_ < sizeof buff_);
}
}
#endif //MONGO_SRC_BASE_LOGSTREAM_H
