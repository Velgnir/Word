
cmake_minimum_required(VERSION 3.17)
enable_language(CXX)
project(untitled15)
find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

add_executable(untitled15 main.cpp src/files.cpp src/counter.cpp)

target_link_libraries(untitled15 ${CMAKE_THREAD_LIBS_INIT})