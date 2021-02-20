cmake_minimum_required(VERSION 3.10)
get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

add_executable(${TARGET} ${src} ${hdr})

target_link_libraries(${TARGET} Qt6::Core Qt6::Gui Qt6::Widgets)

get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/../ $<TARGET_FILE:${TARGET}>
)
