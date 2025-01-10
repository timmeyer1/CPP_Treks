cmake_minimum_required(VERSION 3.16)
project(trek_manager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Trouver les packages requis
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(CURL REQUIRED)
find_package(MySQL REQUIRED)

# Sources du projet
set(SOURCES
    src/main.cpp
    src/database/DatabaseManager.cpp
    src/models/Client.cpp
    src/models/Trek.cpp
    src/models/Reservation.cpp
    src/api/WeatherAPI.cpp
    src/ui/MainWindow.cpp
)

# Création de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Inclusion des répertoires
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${MYSQL_INCLUDE_DIR}
    ${CURL_INCLUDE_DIRS}
)

# Liaison avec les bibliothèques
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    ${CURL_LIBRARIES}
    ${MYSQL_LIBRARIES}
    mysqlclient
)
