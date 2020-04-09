//
// Created by lsmg on 4/9/20.
//

#include <sys/time.h>
#include "Timestamp.h"

using namespace mongo;

const int Timestamp::MS_PER_SECOND;


Timestamp Timestamp::Now()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);

    return Timestamp(tv.tv_sec * MS_PER_SECOND + tv.tv_usec);
}
