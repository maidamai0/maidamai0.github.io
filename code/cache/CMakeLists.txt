cmake_minimum_required(VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${TARGET} CXX)


find_path(NANOBENCH_INCLUDE_DIRS "nanobench.h")
include_directories(${NANOBENCH_INCLUDE_DIRS})

find_package(nlohmann_json CONFIG REQUIRED)
link_libraries(nlohmann_json nlohmann_json::nlohmann_json)

file(GLOB src "*.cpp")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:50000000")

add_executable(${TARGET} ${src})