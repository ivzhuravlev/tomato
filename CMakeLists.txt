cmake_minimum_required(VERSION 3.17.0)

project(tomato)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC on)
set(CMAKE_AUTOUIC on)
set(CMAKE_AUTORCC on)

find_package(Qt5 COMPONENTS Core Widgets Multimedia REQUIRED)

add_executable(tomato 
    clock.h
    clock.cpp
    main.cpp
    mainForm.h
    mainForm.cpp
    pomodoroTimer.h
    pomodoroTimer.cpp
    pomoListWidget.h
    pomoListWidget.cpp
    settingsDialog.h
    settingsDialog.cpp
    settingsSerializer.h
    settingsSerializer.cpp
    timerSettings.h
    timerSettings.cpp
    resources.qrc
)

target_link_libraries(tomato Qt5::Core Qt5::Widgets Qt5::Multimedia)

add_custom_command(
    TARGET tomato POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/res/bell_long.wav
            ${CMAKE_CURRENT_BINARY_DIR}/bell_long.wav)
