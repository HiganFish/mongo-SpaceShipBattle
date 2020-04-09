//
// Created by lsmg on 4/9/20.
//

#ifndef MONGO_SRC_BASE_TIMESTAMP_H
#define MONGO_SRC_BASE_TIMESTAMP_H

#include <cstdint>
namespace mongo
{
class Timestamp
{
public:
    Timestamp():
    ms_since_create(0) {}

    explicit Timestamp(int64_t ms):
    ms_since_create(ms) {}

    static Timestamp Now();

    const static int MS_PER_SECOND = 1000 * 1000;

    int64_t GetMsSinceCreate() const
    { return ms_since_create; }

private:
    int64_t ms_since_create;
};
}
#endif //MONGO_SRC_BASE_TIMESTAMP_H
