cmake_minimum_required(VERSION 3.16)

project(
    NumRepresentation
    DESCRIPTION "A QT Gui."
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# add_subdirectory(src)


find_package(Qt5 REQUIRED COMPONENTS Widgets)


add_executable(NumRep
        src/main.cpp
        src/NumRepWindow.cpp
        src/ClickableLabel.cpp
        src/BinaryEditor.cpp
        src/data_modle/DataModel.h src/edit_fields/FieldTypes.h src/edit_fields/GenericEditField.h src/edit_fields/GenericEditField.cpp src/edit_fields/EditFields.cpp src/edit_fields/EditFields.h)

target_link_libraries(NumRep PRIVATE Qt5::Widgets)
