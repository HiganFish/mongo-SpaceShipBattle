//
// Created by lsmg on 4/8/20.
//

#ifndef MONGO_SRC_NET_EVENTLOOPTHREADPOLL_H
#define MONGO_SRC_NET_EVENTLOOPTHREADPOLL_H

#include <vector>
#include <memory>

namespace mongo
{
namespace net
{
class EventLoop;
class EventLoopThread;

class EventLoopThreadPoll
{
public:
    /**
     * 事件循环线程池 默认没有从线程
     * @param loop 用户创建的事件循环
     */
    explicit EventLoopThreadPoll(EventLoop* loop);
    ~EventLoopThreadPoll();

    /**
     * 创建保存 事件循环线程 保存事件循环
     */
    void Start();

    void SetThreadNums(int nums)
    { thread_num_ = nums; }

    int GetThreadNums() const
    { return thread_num_; }

    EventLoop* GetNextEventLoop();
private:
    /**
     * 保存用户创建的事件循环, 同时作为默认返回事件循环
     */
    EventLoop* baseloop_;
    int thread_num_;
    int next_thread_sub;

    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*>loops_;
};
}
}

#endif //MONGO_SRC_NET_EVENTLOOPTHREADPOLL_H
