add_executable(accept_test accept.cpp)
target_link_libraries(accept_test mongo_net)

add_executable(buffer_test buffer.cpp)
target_link_libraries(buffer_test mongo_net)

add_executable(logger_test logger.cpp)
target_link_libraries(logger_test mongo_net)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/login.pb.h)
add_executable(protobuf_server_test protobuf/ProtobufServerTest.cpp protobuf/login.pb.cc protobuf/login.pb.h)
target_link_libraries(protobuf_server_test mongo_net)

add_executable(protobuf_test protobuf/protobuftest.cpp protobuf/login.pb.cc protobuf/login.pb.h)
target_link_libraries(protobuf_test mongo_net)
endif()