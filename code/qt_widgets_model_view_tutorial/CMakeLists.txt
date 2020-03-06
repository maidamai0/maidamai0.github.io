cmake_minimum_required(VERSION 3.10)
project(model_view CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT5_COMPONENTS
    Core 
    Gui
    Widgets
)

find_package(Qt5 COMPONENTS  ${QT5_COMPONENTS} REQUIRED)

file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

add_executable(${PROJECT_NAME} ${src} ${hdr})

foreach(LIB ${QT5_COMPONENTS})
    target_link_libraries(${PROJECT_NAME} Qt5::${LIB})
endforeach()

