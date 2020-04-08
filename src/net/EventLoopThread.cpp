//
// Created by lsmg on 4/8/20.
//

#include "MutexGuard.h"
#include "EventLoopThread.h"
#include "EventLoop.h"

using namespace mongo;
using namespace mongo::net;

EventLoopThread::EventLoopThread():
loop_(nullptr),
thread_(std::bind(&EventLoopThread::ThreadFunc, this)),
mutex_(),
cond_(mutex_)
{

}
EventLoopThread::~EventLoopThread()
{

}
void EventLoopThread::ThreadFunc()
{
    EventLoop loop;
    loop_ = &loop;
    cond_.WakeUp();
    loop.Loop();
}
EventLoop* EventLoopThread::StartEventLoop()
{
    /**
     * 创建子线程 等待子线程执行 ThreadFunc 唤醒下方的信号量
     */
    thread_.Create();
    EventLoop* loop = nullptr;
    {
        MutexGuard guard(mutex_);
        while (!loop_)
        {
            cond_.Wait();
        }
        loop = loop_;
    }
    return loop;
}
