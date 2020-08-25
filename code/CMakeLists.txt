# dependencies
add_compile_definitions(DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)

find_package(doctest CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(docopt CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
link_libraries(docopt_s fmt::fmt doctest::doctest magic_enum::magic_enum)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/time_measure)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/time_measure/include)
link_libraries(time_measurement)

add_compile_definitions(ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../assets")

# get subdir
# https://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${SUBDIRS})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt)
        message(STATUS "project ${subdir} added")
        add_subdirectory(${subdir})
    endif()
endforeach()
