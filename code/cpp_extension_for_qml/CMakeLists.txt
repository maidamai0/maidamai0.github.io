set(CMAKE_DEBUG_POSTFIX d) 

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Qml Quick REQUIRED)

link_libraries(Qt6::Core Qt6::Qml Qt6::Quick)

add_subdirectory(TimeModule)
add_subdirectory(App)