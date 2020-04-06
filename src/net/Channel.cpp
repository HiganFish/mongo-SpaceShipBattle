//
// Created by lsmg on 4/5/20.
//


#include "EventLoop.h"
#include "Channel.h"

using namespace mongo;
using namespace mongo::net;

Channel::Channel(EventLoop *loop, int fd):
loop_(loop),
fd_(fd),
events_(0),
revents_(0),
status_(ADD)
{

}
Channel::~Channel()
{

}
void Channel::Update()
{
    loop_->UpdateChannel(this);
}
void Channel::HandleEvent()
{
    if (events_ & EPOLLIN)
    {
        if (read_callback_)
        {
            read_callback_();
        }
    }
    if (events_ & EPOLLOUT)
    {
        if (write_callback_)
        {
            write_callback_();
        }
    }
    if (events_ & EPOLLERR)
    {
        if (error_callback_)
        {
            error_callback_();
        }
    }
    if (events_ & EPOLLHUP)
    {
        if (close_callback_)
        {
            close_callback_();
        }
    }
}
