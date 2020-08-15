cmake_minimum_required(VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${TARGET} CXX)

find_package(RapidJSON CONFIG REQUIRED)

file(GLOB src "*.cpp")

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/generate_cpp.py -s ${CMAKE_CURRENT_SOURCE_DIR}/example.json -d ${CMAKE_CURRENT_SOURCE_DIR}/json_message.h
    RESULT_VARIABLE CMD_ERROR
    OUTPUT_FILE CMD_OUTPUT
    )

MESSAGE( STATUS "CMD_ERROR:" ${CMD_ERROR})
MESSAGE( STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})

add_executable(${TARGET} ${src})
target_include_directories(${TARGET} PRIVATE ${RAPIDJSON_INCLUDE_DIRS})