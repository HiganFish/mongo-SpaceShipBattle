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
    LOG_ERROR(__VA_ARGS__) \
    exit(errno); \
}   \

#define LOG_ERROR(...)   \
{   \
    printf("[ERROR][func: %s][line: %d]", __FUNCTION__, __LINE__);  \
    printf(__VA_ARGS__); \
    printf("\n");    \
}   \

#define LOG_WARN(...)   \
{   \
    printf("[WARN][func: %s][line: %d]", __FUNCTION__, __LINE__);  \
    printf(__VA_ARGS__); \
    printf("\n");    \
}   \

#define LOG_INFO(...)   \
{   \
    printf("[INFO][func: %s][line: %d]", __FUNCTION__, __LINE__);  \
    printf(__VA_ARGS__); \
    printf("\n");    \
}   \

//#define LOG_DEBUG(...)   \
//{   \
//    printf(__VA_ARGS__); \
//    printf("\n[DEBUG][file: %s][line: %d]\n", __FILE__, __LINE__);  \
//}   \

#define LOG_DEBUG(...){}

class Log
{

};

#endif //MONGO_SRC_BASE_LOG_H
