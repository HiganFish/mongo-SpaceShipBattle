//
// Created by lsmg on 4/8/20.
//

#ifndef MONGO_SRC_NET_EVENTLOOPTHREAD_H
#define MONGO_SRC_NET_EVENTLOOPTHREAD_H

#include "Condition.h"
#include "Thread.h"

namespace mongo
{
namespace net
{

class EventLoop;

class EventLoopThread
{
public:
    EventLoopThread();
    ~EventLoopThread();

    /**
     * Thread回调函数 负责创建事件循环 启动事件循环
     */
    void ThreadFunc();

    /**
     * 创建线程
     * @return 返回子线程管理的事件循环
     */
    EventLoop* StartEventLoop();
private:

    /**
     * 保存函数创建回调函数中 栈上对象
     */
    EventLoop* loop_;

    Thread thread_;

    Mutex mutex_;
    Condition cond_;
};
}
}
#endif //MONGO_SRC_NET_EVENTLOOPTHREAD_H
