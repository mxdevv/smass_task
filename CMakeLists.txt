cmake_minimum_required(VERSION 2.8)

project(smass_task)

include_directories(${PROJECT_SOURCE_DIR})

find_package(OpenCV REQUIRED)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(client ${OpenCV_LIBS})
target_link_libraries(server ${OpenCV_LIBS})
