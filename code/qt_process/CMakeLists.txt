cmake_minimum_required(VERSION 3.10)
project(qt_process CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT5_COMPONENTS
    Core
)

find_package(Qt5 COMPONENTS ${QT5_COMPONENTS} REQUIRED)

foreach(LIB ${QT5_COMPONENTS})
    link_libraries(Qt5::${LIB})
endforeach()

add_executable(calling calling.cpp)
add_executable(called called.cpp)

get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

add_custom_command(
    TARGET calling
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:calling>
)