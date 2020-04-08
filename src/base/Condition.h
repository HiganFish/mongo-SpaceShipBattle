//
// Created by lsmg on 4/8/20.
//

#ifndef MONGO_SRC_BASE_CONDITION_H
#define MONGO_SRC_BASE_CONDITION_H

#include "Mutex.h"
namespace mongo
{
class Condition : noncopyable
{
public:
    explicit Condition(Mutex& mutex);
    ~Condition();
    void Wait();
    void WakeUp();
    void WakeUpAll();
private:
    Mutex& mutex_;
    pthread_cond_t cond_;
};
}
#endif //MONGO_SRC_BASE_CONDITION_H
