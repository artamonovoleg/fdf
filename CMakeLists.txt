cmake_minimum_required(VERSION 3.17)
project(fdf)

set(CMAKE_CXX_STANDARD 14)

add_executable(fdf main.cpp Map.cpp Map.hpp Point.hpp Interpolate.cpp Interpolate.hpp Surface.cpp Surface.hpp Gui.cpp Gui.hpp Renderer.cpp Renderer.hpp Camera.cpp Camera.hpp Transform.cpp Transform.hpp)
target_link_libraries(fdf sfml-graphics sfml-window sfml-system)