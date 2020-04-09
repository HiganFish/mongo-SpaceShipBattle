//
// Created by lsmg on 4/9/20.
//

#include <algorithm>
#include "LogStream.h"

using namespace mongo;

const int LogStream::MAX_NUMBER_SIZE;

LogStream& LogStream::operator<<(short num)
{
    *this << static_cast<int>(num);
    return *this;
}

LogStream& LogStream::operator<<(unsigned short num)
{
    *this << static_cast<unsigned int>(num);
    return *this;
}

LogStream& LogStream::operator<<(int num)
{
    FormatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(unsigned num)
{
    FormatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(long num)
{
    FormatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long num)
{
    FormatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(long long num)
{
    FormatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long long num)
{
    FormatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(char str)
{
    buffer_.Append(&str, 1);
    return *this;
}

LogStream& LogStream::operator<<(const char* str)
{
    if (str)
    {
        buffer_.Append(str, strlen(str));
    }
    else
    {
        buffer_.Append("(nullptr)", 9);
    }
    return *this;
}

const char digits_character[] = "0123456789";

// LEARN https://www.drdobbs.com/flexible-c-1-efficient-integer-to-string/184401596
template<typename T>
size_t Convert(char buff[], T value)
{
    T i = value;
    char* p = buff;

    do
    {
        unsigned lsd = static_cast<unsigned>(i % 10);
        i /= 10;
        // *p++ = '0' + lsd; 不高效?
        *p++ = digits_character[lsd];
    } while (i != 0);

    if (value < 0)
    {
        *p++ = '-';
    }
    *p = '\0';

    // LEARN 原文中是从buff最后一个字节开始写入 但是这里需要从开头写入 所以改为倒置一下
    std::reverse(buff, p);
    return p - buff;
}

template<typename T>
void LogStream::FormatInteger(T t)
{
    if (buffer_.WriteableBytes() > MAX_NUMBER_SIZE)
    {
        size_t len = Convert(buffer_.WritePeek(), t);
        buffer_.MoveWritePeek(len);
    }
}
