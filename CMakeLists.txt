cmake_minimum_required(VERSION 3.17.0)

project(tomato)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC on)
set(CMAKE_AUTOUIC on)
set(CMAKE_AUTORCC on)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(tomato 
    main.cpp
    mainForm.h
    mainForm.cpp
)

target_link_libraries(tomato Qt5::Core Qt5::Widgets)