#include "Logger.h"

int main()
{
    LOG_DEBUG << 1 << "debug";
    LOG_INFO << 1 << "info";
    LOG_WARN << 1 << "warn";
    LOG_ERROR << 1 << "error";
}
