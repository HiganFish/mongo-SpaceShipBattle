SET(HEADFILES
        EventLoop.h
        multiplexing/MultiBase.h
        Channel.h
        multiplexing/MultiEpoll.h
        multiplexing/MultiSelect.h
        Socket.h
        InetAddress.h
        Acceptor.h
        TcpServer.h
)

SET(SRCFILES
        EventLoop.cpp
        multiplexing/MultiBase.cpp
        Channel.cpp
        multiplexing/MultiEpoll.cpp
        multiplexing/MultiSelect.cpp
        Socket.cpp
        InetAddress.cpp
        Acceptor.cpp
        TcpServer.cpp
)

add_library(mongo_net ${HEADFILES} ${SRCFILES})
target_link_libraries(mongo_net mongo_base)