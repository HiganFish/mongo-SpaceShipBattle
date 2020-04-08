SET(HEADFILES
        noncopyable.h
        Thread.h
        Log.h
        Mutex.h
        Condition.h
        MutexGuard.h
)

SET(SRCFILES
        Thread.cpp
        Log.cpp
        Mutex.cpp
        Condition.cpp
        MutexGuard.cpp
)

add_library(mongo_base ${HEADFILES} ${SRCFILES})
target_link_libraries(mongo_base pthread)
