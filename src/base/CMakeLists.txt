SET(HEADFILES
        noncopyable.h
        Thread.h
        Log.h
)

SET(SRCFILES
        Thread.cpp
        Log.cpp
)

add_library(mongo_base ${HEADFILES} ${SRCFILES})
