//
// Created by lsmg on 4/8/20.
//
#include <Logger.h>
#include "EventLoopThreadPoll.h"
#include "EventLoopThread.h"

using namespace mongo;
using namespace mongo::net;

EventLoopThreadPoll::EventLoopThreadPoll(EventLoop* loop):
baseloop_(loop),
thread_num_(0),
next_thread_sub(0)
{

}
EventLoopThreadPoll::~EventLoopThreadPoll()
{

}
void EventLoopThreadPoll::Start()
{
    LOG_INFO << "extra thread num " << thread_num_;
    for(int i = 0; i < thread_num_; ++i)
    {
        EventLoopThread* thread = new EventLoopThread();
        threads_.push_back(std::unique_ptr<EventLoopThread>(thread));
        loops_.push_back(thread->StartEventLoop());
    }
}
EventLoop* EventLoopThreadPoll::GetNextEventLoop()
{
    EventLoop* loop = baseloop_;

    if (!loops_.empty())
    {
        loop = loops_[next_thread_sub++];
        if (next_thread_sub == thread_num_)
        {
            next_thread_sub = 0;
        }
    }

    return loop;
}
