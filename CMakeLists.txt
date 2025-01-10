cmake_minimum_required(VERSION 3.16)
project(trek_manager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Configuration Qt
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Inclusion des répertoires
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

# Sources
set(SOURCES
    src/main.cpp
    src/ui/MainWindow.cpp
    src/database/DatabaseManager.cpp
    src/models/Client.cpp
    src/models/Trek.cpp
    src/models/Reservation.cpp
    src/api/WeatherAPI.cpp
)

# Création de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Liaison avec Qt
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
)
