project(edpg)

cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGSl} -Wall -pedantic")

add_subdirectory(src)
