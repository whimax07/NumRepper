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


# set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.4\\mingw_64\\bin")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# add_subdirectory(src)


add_executable(NumRep
    src/main.cpp
)

target_link_libraries(NumRep PRIVATE Qt6::Widgets)

