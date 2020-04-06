SET(HEADFILES
        EventLoop.h
        multiplexing/MultiBase.h
        Channel.h
        multiplexing/MultiEpoll.h
        multiplexing/MultiSelect.h
        Socket.h
        InetAddress.h
        Acceptor.h
)

SET(SRCFILES
        EventLoop.cpp
        multiplexing/MultiBase.cpp
        Channel.cpp
        multiplexing/MultiEpoll.cpp
        multiplexing/MultiSelect.cpp
        Socket.h
        InetAddress.h
        Acceptor.h
)

add_library(mongo_net ${HEADFILES} ${SRCFILES})