//
// Created by lsmg on 4/5/20.
//

#ifndef MONGO_SRC_NET_MULTIEPOLL_H
#define MONGO_SRC_NET_MULTIEPOLL_H

#include <vector>
#include <sys/epoll.h>

#include "MultiBase.h"

namespace mongo
{
namespace net
{
class MultiEpoll : public MultiBase
{
public:
    explicit MultiEpoll(EventLoop* loop);

    ~MultiEpoll() override;

    void UpdateChannel(Channel* channel) override;

    void LoopOnce(int msec, ActiveChannelList* channel_list) override;
private:
    int epollfd_;

    const static int EVENT_INIT_NUMBERS = 10;

    std::vector<epoll_event> events_;

    void Update(int ctl, Channel *channel);

    void FillActiveChannelList(int number, ActiveChannelList* channel_list);
};
}
}

#endif //MONGO_SRC_NET_MULTIEPOLL_H
