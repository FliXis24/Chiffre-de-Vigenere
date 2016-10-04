project(Chiffre_de_Vigenere)
cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic-errors -std=c++14")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED Core Sql Qml Quick QuickControls2 QuickWidgets Gui Widgets)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

qt5_use_modules(${PROJECT_NAME} Core Sql Qml Quick QuickControls2 QuickWidgets Gui Widgets)
