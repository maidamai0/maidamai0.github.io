cmake_minimum_required(VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${TARGET} CXX)

file(GLOB src "*.cpp")

add_executable(parent parent.cpp)
add_executable(child child.cpp)
add_dependencies(parent child)
add_compile_definitions(ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")