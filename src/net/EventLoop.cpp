//
// Created by lsmg on 4/5/20.
//

#include "EventLoop.h"
#include "multiplexing/MultiBase.h"
#include "multiplexing/MultiEpoll.h"
#include "Channel.h"

using namespace mongo;
using namespace mongo::net;

EventLoop::EventLoop():
multi_base_(MultiBase::InitMulti(this)),
looping_(false)
{

}
EventLoop::~EventLoop()
{

}
void EventLoop::Loop()
{
    while (looping_)
    {
        active_channel_list.clear();

        multi_base_->LoopOnce(10, &active_channel_list);

        for (Channel* channel : active_channel_list)
        {
            channel->HandleEvent();
        }
    }
}
void EventLoop::UpdateChannel(Channel* channel)
{
    multi_base_->UpdateChannel(channel);
}
void EventLoop::Start()
{
    looping_ = true;
    Loop();
}