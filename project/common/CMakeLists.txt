SET(LOGIN_SERVER_HEADER_FILES
        login.pb.h
)

SET(LOGIN_SERVER_SRC_FILES
        login.pb.cc
        LoginServer.cpp
)

add_executable(common-login ${LOGIN_SERVER_HEADER_FILES} ${LOGIN_SERVER_SRC_FILES})
target_link_libraries(common-login mongo_net)

SET(PLAY_SERVER_HEADER_FILES
        play.pb.h
)

SET(PLAY_SERVER_SRC_FILES
        play.pb.cc
        PlayServer.cpp
)
add_executable(common-play ${PLAY_SERVER_HEADER_FILES} ${PLAY_SERVER_SRC_FILES})
target_link_libraries(common-play mongo_net)