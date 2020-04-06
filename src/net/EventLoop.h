//
// Created by lsmg on 4/5/20.
//

#ifndef MONGO_SRC_NET_EVENTLOOP_H
#define MONGO_SRC_NET_EVENTLOOP_H

#include <vector>
#include <memory>

namespace mongo
{
namespace net
{
class Channel;
class MultiBase;
class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    void Loop();

    void Start();

    void UpdateChannel(Channel *channel);

private:

    bool looping_;

    std::unique_ptr<MultiBase> multi_base_;

    typedef std::vector<Channel*> ActiveChannelList;
    ActiveChannelList active_channel_list;

};
}
}

#endif //MONGO_SRC_NET_EVENTLOOP_H
