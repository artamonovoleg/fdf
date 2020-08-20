cmake_minimum_required(VERSION 3.17)
project(fdf)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(fdf main.cpp Map.cpp Map.hpp)
target_link_libraries(fdf sfml-graphics sfml-window sfml-system)