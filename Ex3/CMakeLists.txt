cmake_minimum_required(VERSION 3.12.2)
project(Ex3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex3 main.cpp Camera.h)

target_link_libraries(Ex3 libSOIL.a libopengl32.a libglu32.a libfreeglut.a)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)