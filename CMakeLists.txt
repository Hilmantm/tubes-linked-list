cmake_minimum_required(VERSION 3.20)
project(linked_list)

set(CMAKE_CXX_STANDARD 14)

add_executable(linked_list main.cpp event.h participant.h app.h app.cpp)
