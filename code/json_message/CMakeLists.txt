cmake_minimum_required(VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${TARGET} CXX)

find_package(RapidJSON CONFIG REQUIRED)

file(GLOB src "*.cpp")

add_executable(${TARGET} ${src})
target_include_directories(${TARGET} PRIVATE ${RAPIDJSON_INCLUDE_DIRS})