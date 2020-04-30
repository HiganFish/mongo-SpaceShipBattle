SET(HEADFILES
        ProtobufCodec.h
        ProtobufServer.h
        Dispatcher.h
)

SET(SRCFILES
        ProtobufCodec.cpp
        ProtobufServer.cpp
)

add_library(mongo_protobuf ${HEADFILES} ${SRCFILES})
target_link_libraries(mongo_protobuf mongo_net protobuf z)