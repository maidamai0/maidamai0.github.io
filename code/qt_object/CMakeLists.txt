get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)

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

file(GLOB src "*.cpp")

add_executable(${TARGET} ${src})
target_link_libraries(${TARGET} PRIVATE fmt::fmt-header-only)

get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:${TARGET}>
)