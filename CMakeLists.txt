cmake_minimum_required(VERSION 3.10)

project(sites_code CXX)
set(CMAKE_CXX_STANDARD 17)

option(USE_CLANG_TIDY "If use Clang-tidy" ON)

set(CMAKE_GENERATOR "Ninja")

include(cmake-qmlplugin/QmlPlugin.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(USE_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy --fix --fix-errors)
endif(USE_CLANG_TIDY)


add_subdirectory(code)