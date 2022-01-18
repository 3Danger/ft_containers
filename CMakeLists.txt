cmake_minimum_required(VERSION 3.5)
#project(ft_containers)
set(BINARY ${CMAKE_PROJECT_NAME})
FILE(GLOB CPP *.cpp)
FILE(GLOB HPP *.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -g -std=c++98 -I.")

add_executable(${BINARY} main.cpp)