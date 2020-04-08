//
// Created by lsmg on 4/8/20.
//

#include "Condition.h"

using namespace mongo;

Condition::Condition(Mutex& mutex):
mutex_(mutex),
cond_()
{
    pthread_cond_init(&cond_, nullptr);
}
Condition::~Condition()
{
    pthread_cond_destroy(&cond_);
}
void Condition::Wait()
{
    pthread_cond_wait(&cond_, mutex_.GetMutex());
}
void Condition::WakeUp()
{
    pthread_cond_signal(&cond_);
}
void Condition::WakeUpAll()
{
    pthread_cond_broadcast(&cond_);
}
