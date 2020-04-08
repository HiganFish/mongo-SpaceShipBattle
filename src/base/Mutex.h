//
// Created by lsmg on 4/8/20.
//

#ifndef MONGO_SRC_BASE_MUTEX_H
#define MONGO_SRC_BASE_MUTEX_H

#include <pthread.h>
#include "noncopyable.h"

namespace mongo
{
class Mutex : noncopyable
{
public:
    Mutex();
    ~Mutex();

    void Lock();

    void UnLock();

    pthread_mutex_t* GetMutex();

private:
    pthread_mutex_t mutex_;
};
}
#endif //MONGO_SRC_BASE_MUTEX_H
