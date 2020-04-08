//
// Created by lsmg on 4/5/20.
//

#ifndef MONGO_SRC_BASE_THREAD_H
#define MONGO_SRC_BASE_THREAD_H

#include <functional>
#include <pthread.h>
#include "noncopyable.h"
namespace mongo
{
class Thread : noncopyable
{
public:
    typedef std::function<void()> ThreadFunc;
    explicit Thread(ThreadFunc cb);
    ~Thread();

    void Create();
private:
    ThreadFunc func_;

    pthread_t thread_id_;
};
}

#endif //MONGO_SRC_BASE_THREAD_H
