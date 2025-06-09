cmake_minimum_required(VERSION 3.16)
project(DatabaseConnectionDialog LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    dbdialog.cpp
    dbdialog.h
    dbdialog.ui
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
