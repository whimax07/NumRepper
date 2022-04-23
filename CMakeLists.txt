cmake_minimum_required(VERSION 3.16)

project(
    NumRepresentation
    DESCRIPTION "A QT Gui."
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# add_subdirectory(src)


find_package(Qt5 REQUIRED COMPONENTS Widgets)


add_executable(NumRep
        src/main.cpp
        src/NumRepWindow.h
        src/NumRepWindow.cpp
        src/ClickableLabel.cpp src/ClickableLabel.h src/BinaryEditor.cpp src/BinaryEditor.h)

target_link_libraries(NumRep PRIVATE Qt5::Widgets)
