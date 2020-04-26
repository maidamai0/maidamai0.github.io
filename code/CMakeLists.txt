# dependencies
add_subdirectory(dependencies/fmt)
add_subdirectory(dependencies/time_measure)
set(depends 
  fmt/include
  time_measure/include
)
foreach(dep ${depends})
  message(STATUS "include path ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${dep}")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${dep})
endforeach()
link_libraries(fmt::fmt)
link_libraries(time_measurement)

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
