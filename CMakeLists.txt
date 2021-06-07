cmake_minimum_required(VERSION 3.5)

project(Muty LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets DBus REQUIRED)

find_library(LO lo REQUIRED)

add_executable(Muty
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
    mainwindow.ui
    )

target_link_libraries(Muty PRIVATE Qt::Widgets Qt::DBus lo)
