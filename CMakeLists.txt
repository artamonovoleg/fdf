cmake_minimum_required(VERSION 3.17)
project(sfml)

set(CMAKE_CXX_STANDARD 14)

add_executable(sfml main.cpp Map.cpp Map.hpp)
target_link_libraries(sfml sfml-graphics sfml-window sfml-system)