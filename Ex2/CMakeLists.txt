cmake_minimum_required(VERSION 3.12.2)
project(rotate)

set(CMAKE_CXX_STANDARD 14)

add_executable(rotate main.cpp Camera.h)

target_link_libraries(rotate libSOIL.a libopengl32.a libglu32.a libfreeglut.a)