SET(HEADFILES
        noncopyable.h
        Thread.h
        Mutex.h
        Condition.h
        MutexGuard.h
        Logger.h
        LogStream.h
        Timestamp.h
)

SET(SRCFILES
        Thread.cpp
        Mutex.cpp
        Condition.cpp
        MutexGuard.cpp
        Logger.cpp
        LogStream.cpp
        Timestamp.cpp
)

add_library(mongo_base ${HEADFILES} ${SRCFILES})
target_link_libraries(mongo_base pthread)
