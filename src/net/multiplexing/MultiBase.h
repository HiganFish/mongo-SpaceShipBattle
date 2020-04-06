//
// Created by lsmg on 4/5/20.
//

#ifndef MONGO_SRC_NET_MULTIBASE_H
#define MONGO_SRC_NET_MULTIBASE_H

#include <vector>
#include "noncopyable.h"

namespace mongo
{
namespace net
{
class EventLoop;
class Channel;
class MultiBase : noncopyable
{
public:
    typedef std::vector<Channel*> ActiveChannelList;

    explicit MultiBase(EventLoop* loop);
    virtual ~MultiBase();

    virtual void UpdateChannel(Channel* channel);

    virtual void LoopOnce(int msec, ActiveChannelList* channel_list);

    static MultiBase* InitMulti(EventLoop *loop);

private:
    EventLoop* loop_;
};
}
}

#endif //MONGO_SRC_NET_MULTIBASE_H
