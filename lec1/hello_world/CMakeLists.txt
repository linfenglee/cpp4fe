cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(hello_world)

set(hello_world_files hello_world.cpp main.cpp)

add_executable(hello_world ${hello_world_files})

