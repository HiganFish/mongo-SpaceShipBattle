//
// Created by lsmg on 4/5/20.
//

#include "Thread.h"
#include "Log.h"
#include <utility>


using namespace mongo;


struct ThreadData
{
    typedef Thread::ThreadFunc ThreadFunc;
    explicit ThreadData(ThreadFunc f):func(std::move(f)) {}
    ThreadFunc func;
};

void* ThreadFuncInternal(void* args)
{
    ThreadData* data = static_cast<ThreadData*>(args);
    if (data != nullptr)
    {
        if (data->func)
        {
            data->func();
        }
    }
    delete data;
    return nullptr;
}


Thread::Thread(Thread::ThreadFunc  cb):
func_(std::move(cb)),
thread_id_()
{
}
Thread::~Thread()
{

}
void Thread::Create()
{
    /**
     * 原来是下面这样写的, 然而pthread_create是非阻塞, Create函数执行玩 data就析构了
     * ThreadFuncInternal函数中调用 data的时候访问了垂悬指针自然报错
     */
    // ThreadData data(func_);

    ThreadData *data = new ThreadData(func_);
    pthread_create(&thread_id_, nullptr, ThreadFuncInternal, (void*)data);
}
