//
// Created by lsmg on 4/5/20.
//

#ifndef MONGO_SRC_BASE_THREAD_H
#define MONGO_SRC_BASE_THREAD_H

#include <functional>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
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

namespace CurrentThread
{

    //　LEARN __thread 为每个线程设置缓存
    extern __thread int t_cached_tid;
    extern __thread char t_tid_string[32];
    extern __thread int t_tid_stringlength;

    inline int Tid()
    {
        // LEARN __builtin_expect(a, b) a的结果bool值 更倾向于b 用于优化汇编指令
        if (__builtin_expect(t_cached_tid == 0, 0))
        {
            t_cached_tid = static_cast<pid_t>(::syscall(SYS_gettid));
            t_tid_stringlength = snprintf(t_tid_string, sizeof t_tid_string, "%5d ", t_cached_tid);
        }
        return t_cached_tid;
    }

    inline const char* TidString()
    {
        return t_tid_string;
    }

    inline int TidStringLength()
    {
        return t_tid_stringlength;
    }
}
}

#endif //MONGO_SRC_BASE_THREAD_H
