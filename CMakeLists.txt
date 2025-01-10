cmake_minimum_required(VERSION 3.1.0)

project(trek_manager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(MySQL REQUIRED)

set(SOURCES
    src/main.cpp
    src/database/DatabaseManager.cpp
    src/models/Client.cpp
    src/models/Trek.cpp
    src/models/Reservation.cpp
    src/api/WeatherAPI.cpp
    src/ui/MainWindow.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    MySQL::MySQL
)
