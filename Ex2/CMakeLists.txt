cmake_minimum_required(VERSION 3.12.2)
project(Ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex2 main.cpp Camera.h)

target_link_libraries(Ex2 libSOIL.a libopengl32.a libglu32.a libfreeglut.a)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/metal.jpg
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wood.jpg
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)