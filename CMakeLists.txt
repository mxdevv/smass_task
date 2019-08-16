cmake_minimum_required(VERSION 2.8)

project(smass_task)

include_directories(${PROJECT_SOURCE_DIR})

find_package(OpenCV REQUIRED)

add_executable(server server.cpp)
add_executable(client client.cpp)

set_property(TARGET server PROPERTY CXX_STANDARD 14)
set_property(TARGET client PROPERTY CXX_STANDARD 14)

target_link_libraries(client ${OpenCV_LIBS})
target_link_libraries(server ${OpenCV_LIBS})
