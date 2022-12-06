
# ==============================================================================
# ===== GUI common lib. ========================================================
add_library(NumRepCommon
        common/NumberStructs.h
        )
# ----- End of GUI common lib section. -----------------------------------------



# ==============================================================================
# ===== RepParse lib. ==========================================================
# This builds the tests.
add_library(RepParseLib STATIC
        parse/Tokenizer.h parse/Tokenizer.cpp
        parse/RepParse.h parse/RepParse.cpp
        parse/tree/AST.h
        parse/token/Operator.h
        parse/token/Token.h
        parse/token/Binary.h
        parse/token/Unary.h
        parse/token/NumericToken.h
        parse/token/End.h
        parse/token/Sentinel.h
        parse/token/Brackets.h
        parse/token/Compare.h
        parse/token/Symbols.h
        parse/utils/Utils.h
        )
# ----- End of RepParse lib section. -------------------------------------------



# ==============================================================================
# ===== GUI executable. ========================================================
add_library(NumRepGUI
        gui/main.cpp
        gui/NumRepWindow.cpp
        gui/data_model/DataModel.h gui/edit_fields/E_FieldTypes.h gui/edit_fields/GenericEditField.h gui/edit_fields/EditFields.cpp gui/edit_fields/EditFields.h gui/binary_rep/BitButtons.h gui/binary_rep/BitButtons.cpp gui/word_size/WordSizeSelection.h gui/word_size/E_WordSizes.h gui/word_size/WordSizeRadioButton.h gui/utils/Utils.cpp gui/utils/Utils.h gui/edit_fields/E_DataUpdateErrors.h
        )

target_link_libraries(NumRepGUI
        PRIVATE Qt5::Widgets
        PRIVATE NumRepCommon
        )

# This is the best solution i currently know of to remove the
# '#include "../utils/Util.h"` problem.
target_include_directories(NumRepGUI
        # Adding GUI makes relative paths from this address available to
        # `#include`.
        PRIVATE gui
        PRIVATE .
        )
# ----- End of GUI executable section. -----------------------------------------
