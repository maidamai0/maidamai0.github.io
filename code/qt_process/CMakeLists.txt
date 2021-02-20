cmake_minimum_required(VERSION 3.10)
project(qt_process CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Qt6_COMPONENTS
    Core
)

find_package(Qt6 COMPONENTS ${Qt6_COMPONENTS} REQUIRED)

foreach(LIB ${Qt6_COMPONENTS})
    link_libraries(Qt6::${LIB})
endforeach()

add_executable(calling calling.cpp)
add_executable(called called.cpp)

get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

add_custom_command(
    TARGET calling
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:calling>
)