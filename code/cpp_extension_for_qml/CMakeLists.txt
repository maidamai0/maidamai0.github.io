set(CMAKE_DEBUG_POSTFIX d) 

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)

link_libraries(Qt5::Core Qt5::Qml Qt5::Quick)

add_subdirectory(TimeModule)
add_subdirectory(App)