cmake_minimum_required(VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${TARGET} CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT5_COMPONENTS
    Core
    Quick
    QuickWidgets
    Qml
)

find_package(Qt5 COMPONENTS ${QT5_COMPONENTS} REQUIRED)

foreach(LIB ${QT5_COMPONENTS})
    link_libraries(Qt5::${LIB})
endforeach()

include_directories(${Qt5Quick_PRIVATE_INCLUDE_DIRS}) # for private headers

file(GLOB src "*.cpp")

add_executable(${TARGET} ${src} resource.qrc)

get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/../ $<TARGET_FILE:${TARGET}>
)

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/../update_resource.py ${CMAKE_CURRENT_SOURCE_DIR})