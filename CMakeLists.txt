cmake_minimum_required(VERSION 3.5)

project(DataViewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(DataViewer
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/dataparser.cpp
    src/dataparser.h
    src/data.h
    src/data.cpp
    src/graphwidget.cpp
    src/graphwidget.h
  )

target_link_libraries(DataViewer PRIVATE Qt5::Widgets)
