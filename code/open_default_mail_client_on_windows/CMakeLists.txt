cmake_minimum_required(VERSION 3.10)
project(send_mail CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui REQUIRED)

file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

add_executable(send_mail ${src} ${hdr})

target_link_libraries(send_mail Qt6::Core Qt6::Gui)

add_executable(mapi mapi.cxx)
