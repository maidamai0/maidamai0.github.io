cmake_minimum_required(VERSION 3.10)

project(sites_code CXX)

include(cmake-qmlplugin/QmlPlugin.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy --fix --fix-errors)

add_subdirectory(code)