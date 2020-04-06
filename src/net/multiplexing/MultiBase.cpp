//
// Created by lsmg on 4/5/20.
//

#include "MultiBase.h"
#include "MultiEpoll.h"

using namespace mongo;
using namespace mongo::net;

MultiBase::MultiBase(EventLoop* loop):
loop_(loop)
{

}
MultiBase::~MultiBase()
{

}
void MultiBase::UpdateChannel(Channel* channel)
{

}

void MultiBase::LoopOnce(int msec, ActiveChannelList* channel_list)
{

}
MultiBase* MultiBase::InitMulti(EventLoop* loop)
{
    return new MultiEpoll(loop);
}
