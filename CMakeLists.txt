cmake_minimum_required( VERSION 3.0 )

#project name
project( luminate )

#flags


#files


#include
include_directories( ./include ./src)

#target
add_executable( luminate ./src/main.cpp ./src/window.cpp ./src/widget.cpp)

target_link_libraries( luminate glfw)
target_link_libraries( luminate GL)