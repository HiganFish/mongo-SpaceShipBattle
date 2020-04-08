
add_executable(accept_test accept.cpp)
target_link_libraries(accept_test mongo_net)

add_executable(buffer_test buffer.cpp)
target_link_libraries(buffer_test mongo_net)