//
// Created by lsmg on 4/5/20.
//

#ifndef MONGO_SRC_NET_CHANNEL_H
#define MONGO_SRC_NET_CHANNEL_H

#include <cstdint>
#include <functional>
#include <sys/epoll.h>
namespace mongo
{
namespace net
{

class EventLoop;
class Channel
{
public:
    typedef std::function<void()> EventCallback;

    enum ChannelStatus {ADD, ADDED, DELED};

    Channel(EventLoop *loop, int fd);
    ~Channel();

    ChannelStatus GetStatus() const
    { return status_; }

    void SetStatus(ChannelStatus status)
    { status_ = status; }

    int GetFd() const
    { return fd_; }

    uint32_t GetREvents() const
    { return revents_; }

    void SetEvents(uint32_t event)
    { events_ = event; }

    void EnableReading()
    { revents_ |= EPOLLIN; Update(); }
    void DisableReading()
    { revents_ &= ~EPOLLIN; Update(); }

    void EnableWriting()
    { revents_ |= EPOLLOUT; Update(); }
    void DisableWriting()
    { revents_ &= ~EPOLLOUT; Update(); }

    void DisableAll()
    { revents_ = 0; Update(); }

    void HandleEvent();

    void SetReadCallback(const EventCallback& read_callback)
    { read_callback_ = read_callback; }

    void SetWriteCallback(const EventCallback& write_callback)
    { write_callback_ = write_callback; }

    void SetErrorCallback(const EventCallback& error_callback)
    { error_callback_ = error_callback; }

    void SetCloseCallback(const EventCallback& close_callback)
    { close_callback_ = close_callback; }
private:

    EventLoop *loop_;

    const int fd_;

    /**
     * 回调事件
     */
    uint32_t events_;

    /**
     * epoll 事件
     */
    uint32_t revents_;
    ChannelStatus status_;

    EventCallback read_callback_;
    EventCallback write_callback_;
    EventCallback error_callback_;
    EventCallback close_callback_;

    void Update();
};

}
}

#endif //MONGO_SRC_NET_CHANNEL_H
