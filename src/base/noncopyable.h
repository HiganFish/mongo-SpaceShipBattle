//
// Created by lsmg on 4/5/20.
//

#ifndef MONGO_SRC_BASE_NONCOPYABLE_H
#define MONGO_SRC_BASE_NONCOPYABLE_H

namespace mongo
{

/**
 * 禁用拷贝构造函数 和 赋值运算符
 */
class noncopyable
{
public:
    noncopyable() = default;
    ~noncopyable() = default;

    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;
private:
};

}

#endif //MONGO_SRC_BASE_NONCOPYABLE_H
