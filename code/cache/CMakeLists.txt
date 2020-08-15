cmake_minimum_required(VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${TARGET} CXX)


find_path(NANOBENCH_INCLUDE_DIRS "nanobench.h")
include_directories(${NANOBENCH_INCLUDE_DIRS})

file(GLOB src "*.cpp")

add_executable(${TARGET} ${src})