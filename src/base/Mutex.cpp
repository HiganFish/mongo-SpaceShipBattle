//
// Created by lsmg on 4/8/20.
//

#include "Mutex.h"

using namespace mongo;

Mutex::Mutex()
{
    pthread_mutex_init(&mutex_, nullptr);
}
Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutex_);
}
void Mutex::Lock()
{
    pthread_mutex_lock(&mutex_);
}
void Mutex::UnLock()
{
    pthread_mutex_unlock(&mutex_);
}
pthread_mutex_t* Mutex::GetMutex()
{
    return &mutex_;
}
