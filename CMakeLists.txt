cmake_minimum_required(VERSION 3.22)

project(
        NumRepresentation
        DESCRIPTION "A QT Gui."
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# ==============================================================================
# ===== QT stuff. ==============================================================
find_package(Qt5 REQUIRED COMPONENTS Widgets)
# ----- End of a QT section. ---------------------------------------------------



# ==============================================================================
# ===== Google stuff. ==========================================================
# This grabs GTest stuff.
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
# I think commenting this out will disable tests.
enable_testing()
# ----- End of a Google section. -----------------------------------------------



# ==============================================================================
# ===== Parse tests. ===========================================================
# This should ask the CMakeList.txt in the lib dir to compile its contents.
add_subdirectory(src/parse)

# This builds the tests.
add_executable(RepParseTests
        tests/BasicTokenizerTests.cpp
        tests/AstCreationTests.cpp
        tests/TokenTests.cpp
        tests/AstEvalTests.cpp
        )

# This links everything together. RepParseLib is set to static in its CMake.
target_link_libraries(
        RepParseTests
        GTest::gtest_main
        RepParseLib
        )

# I am not 100% sure this is correct as I don't know when PROJECT_SOURCE_DIR is
# populated... or what it would be.
target_include_directories(RepParseTests PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/src/parse"
        )
# ----- End of parse tests section. --------------------------------------------



# ==============================================================================
# ===== GUI executable. ========================================================
add_executable(NumRep
        src/gui/main.cpp
        src/gui/NumRepWindow.cpp
        src/gui/data_model/DataModel.h src/gui/edit_fields/E_FieldTypes.h src/gui/edit_fields/GenericEditField.h src/gui/edit_fields/EditFields.cpp src/gui/edit_fields/EditFields.h src/gui/binary_rep/BitButtons.h src/gui/binary_rep/BitButtons.cpp src/gui/word_size/WordSizeSelection.h src/gui/word_size/E_WordSizes.h src/gui/word_size/WordSizeRadioButton.h src/gui/utils/Utils.cpp src/gui/utils/Utils.h src/gui/edit_fields/E_DataUpdateErrors.h
        )



target_link_libraries(NumRep PRIVATE Qt5::Widgets RepParseLib)
# ----- End of GUI executable section. -----------------------------------------


# ==============================================================================
# ===== Google stuff. ==========================================================
# The google has just kind of worked.
include(GoogleTest)
gtest_discover_tests(RepParseTests)
# ----- End of a Google section. -----------------------------------------------
