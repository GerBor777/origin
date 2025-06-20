
cmake_minimum_required(VERSION 3.5)

project(UDPDatagramApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Network REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    udpworker.cpp
    udpworker.h
)

qt_add_executable(UDPDatagramApp
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(UDPDatagramApp PRIVATE Qt6::Widgets Qt6::Network)

qt_finalize_executable(UDPDatagramApp)
