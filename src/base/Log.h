//
// Created by lsmg on 4/5/20.
//

#ifndef MONGO_SRC_BASE_LOG_H
#define MONGO_SRC_BASE_LOG_H

#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#define EXIT_IF(r, ...) \
if (r)  \
{   \
    printf(__VA_ARGS__);    \
    printf("\n[ERROR][file: %s][line: %d][errno: %d] %s\n", __FILE__, __LINE__, errno, strerror(errno));  \
    exit(errno); \
}   \


#define LOG_WARN(...)   \
{   \
    printf(__VA_ARGS__); \
    printf("\n[ERROR][file: %s][line: %d]\n", __FILE__, __LINE__);  \
}   \

#define LOG_INFO(...)   \
{   \
    printf(__VA_ARGS__); \
    printf("\n[INFO][file: %s][line: %d]\n", __FILE__, __LINE__);  \
}   \

#define LOG_DEBUG(...)   \
{   \
    printf(__VA_ARGS__); \
    printf("\n[DEBUG][file: %s][line: %d]\n", __FILE__, __LINE__);  \
}   \

class Log
{

};

#endif //MONGO_SRC_BASE_LOG_H
