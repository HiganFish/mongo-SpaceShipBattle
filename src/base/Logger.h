//
// Created by lsmg on 4/9/20.
//

// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MONGO_SRC_BASE_LOGGER_H
#define MONGO_SRC_BASE_LOGGER_H

#include <cstring>
#include "LogStream.h"
#include "Timestamp.h"

namespace mongo
{
class Logger
{
public:
    enum LogLevel
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS /* 仅用于表示LogLevel元素个数 不做实际使用 */
    };

    class SourceFile
    {
    public:
        /**
         * 数组的引用 使数组在传参时不会降为 指针
         */
        template<int N>
        SourceFile(const char (&arr)[N]):
        data_(arr),
        size_(N - 1)
        {
            const char* name = strrchr(data_, '/'); /* /name */
            if (name)
            {
                data_ = name + 1;
                size_ -= static_cast<int>(data_ - arr);
            }
        }

        const char* data_;
        int size_;
    };

    Logger(LogLevel level, SourceFile file, int line, const char* func);
    Logger(LogLevel level, SourceFile file, int line);
    ~Logger();

    LogStream& GetStream()
    {
        return impl_.stream_;
    }

    static LogLevel GetLogLevel();
    static void SetLogLevel(LogLevel level);

private:

    class Impl
    {
    public:
        typedef Logger::LogLevel LogLevel;
        Impl(LogLevel level, const SourceFile& file, int line);
        void FormatTime();
        void Finish();

        Timestamp time_;
        LogStream stream_;
        LogLevel level_;
        SourceFile filename_;
        int line_;
    };

    Impl impl_;
};
}

extern mongo::Logger::LogLevel g_log_level;
inline mongo::Logger::LogLevel mongo::Logger::GetLogLevel()
{
    return g_log_level;
}


#define LOG_DEBUG if (mongo::Logger::GetLogLevel() <= mongo::Logger::DEBUG) \
  mongo::Logger(mongo::Logger::DEBUG, __FILE__, __LINE__, __func__).GetStream()
#define LOG_INFO if (mongo::Logger::GetLogLevel() <= mongo::Logger::INFO) \
  mongo::Logger(mongo::Logger::INFO, __FILE__, __LINE__).GetStream()
#define LOG_WARN mongo::Logger(mongo::Logger::WARN, __FILE__, __LINE__).GetStream()
#define LOG_ERROR mongo::Logger(mongo::Logger::ERROR, __FILE__, __LINE__).GetStream()
#define LOG_FATAL mongo::Logger(mongo::Logger::FATAL, __FILE__, __LINE__).GetStream()

#endif //MONGO_SRC_BASE_LOGGER_H
