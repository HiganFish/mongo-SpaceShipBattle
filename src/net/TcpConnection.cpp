//
// Created by lsmg on 4/7/20.
//

#include <Logger.h>
#include "TcpConnection.h"
#include "Socket.h"
#include "Channel.h"

using namespace mongo;
using namespace mongo::net;

TcpConnection::TcpConnection(EventLoop* loop, const std::string& connection_name, int sockfd, const InetAddress& host_addr, const InetAddress& client_addr):
loop_(loop),
connection_name_(connection_name),
status_(CONNECTING),
socket_(new Socket(sockfd)),
channel_(new Channel(loop_, socket_->GetFd())),
host_addr_(host_addr),
client_addr_(client_addr)
{
    channel_->SetReadCallback(std::bind(&TcpConnection::ReadHandle, this));
    channel_->SetWriteCallback(std::bind(&TcpConnection::WriteHandle, this));
    channel_->SetErrorCallback(std::bind(&TcpConnection::ErrorHandle, this));
    channel_->SetCloseCallback(std::bind(&TcpConnection::CloseHandle, this));
}
TcpConnection::~TcpConnection()
{

}

void TcpConnection::ReadHandle()
{
    int bytes = input_buffer_.ReadFromFd(socket_->GetFd());
    if (bytes == 0)
    {
        CloseHandle();
    }
    else if (bytes == -1)
    {
        ErrorHandle();
    }
    else
    {
        if (message_callback_)
        {
            message_callback_(shared_from_this(), &input_buffer_);
        }
    }

}
void TcpConnection::WriteHandle()
{
    if (status_ == CONNECTED)
    {
        int ret = socket_->Send(output_buffer_.ReadBegin(), output_buffer_.ReadableBytes());
        if (ret < 0)
        {
            ErrorHandle();
        }
        if (ret == output_buffer_.ReadableBytes())
        {
            channel_->DisableWriting();
            if (write_over_callback_)
            {
                write_over_callback_(shared_from_this());
            }
        }
        output_buffer_.AddReadIndex(ret);
    }
}

void TcpConnection::ErrorHandle()
{
    if (status_ == CONNECTED)
    {
        LOG_ERROR << "A error happend on " << connection_name_ << " errno: " << errno << " errrormsg: " << strerror(errno);
        CloseHandle();
    }

}
void TcpConnection::CloseHandle()
{
    // 关闭会触发 读回调read==0 和 关闭回调 但只能调用一次关闭函数
    if (status_ == CONNECTED)
    {
        status_ = CLOSEING;
        channel_->DisableAll();

        if (close_callback_)
        {
            close_callback_(shared_from_this());
        }
    }
}

void TcpConnection::Send(const char* msg, size_t len)
{
    if (status_ == CONNECTED)
    {
        int ret = socket_->Send(msg, len);
        if (ret < 0)
        {
            ErrorHandle();
        }
        else if (ret < len)
        {
            output_buffer_.Append(msg + ret, len - ret);
            channel_->EnableWriting();
        }
        else
        {
            if (write_over_callback_)
            {
                write_over_callback_(shared_from_this());
            }
        }
    }
}
void TcpConnection::ConnectionCreated()
{
    if (status_ == CONNECTING)
    {
        status_ = CONNECTED;
        channel_->EnableReading();
    }
}
void TcpConnection::CloseConnection()
{
    CloseHandle();
}
