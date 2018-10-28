cmake_minimum_required(VERSION 3.12)
project(Ex1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex1 main.cpp custom_types.h)

target_link_libraries(Ex1 libopengl32.a libglu32.a libfreeglut.a)