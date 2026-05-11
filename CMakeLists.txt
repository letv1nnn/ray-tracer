cmake_minimum_required(VERSION 3.20)

project(ray-tracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ray-tracer src/main.cpp src/vec3.cpp)

target_include_directories(ray-tracer PRIVATE include)
