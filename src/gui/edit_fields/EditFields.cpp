//
// Created by max on 12/06/22.
//

#include <sstream>

#include "EditFields.h"
#include "../utils/Utils.h"
#include "E_DataUpdateErrors.h"
#include "NumberStructs.h"


#define CPP_LOCAL_FUN static



// =============================================================================
// ===== Utils =================================================================

CPP_LOCAL_FUN void invalidArgumentError(
        const std::invalid_argument& error,
        DataModel *dataModel
) {
    std::cout << "std::invalid_argument::what(): "
              << std::endl
              << error.what()
              << std::endl;
}


CPP_LOCAL_FUN void outOfRangeError(
        const std::out_of_range& error,
        DataModel *dataModel
) {
    std::cout << "std::out_of_range::what(): "
              << std::endl
              << error.what()
              << std::endl;
}


/**
 * An Unsigned version of this function is needed as std::stoi will fail if the
 * in `text` is larger than `U32.MAX_VALUE` which `U32.MAX_VALUE` is.
 */
CPP_LOCAL_FUN bool
dataChangedIntoSignedInt(
        const QString &text,
        DataModel *dataModel,
        Number &data
) {
    auto textStd = text.toStdString();
    std::size_t pos = 0;

    if (textStd.length() == 0) {
        dataModel->setNumberEmpty(true);
        data = Number();
        return true;
    }

    long long parsedNumber = 0;
    try {
        parsedNumber = std::stoll(textStd, &pos, 10);
    }
    catch(std::invalid_argument const& ex) {
        invalidArgumentError(ex, dataModel);
        return false;
    }
    catch(std::out_of_range const& ex) {
        outOfRangeError(ex, dataModel);
        return false;
    }

    switch (dataModel->getWordSize()) {
        case E_WordSizes::U8:
            if (parsedNumber > INT8_MAX) return false;
            if (parsedNumber < INT8_MIN) return false;
            data.i8 = static_cast<int8_t>(parsedNumber);
            break;
        case E_WordSizes::U16:
            if (parsedNumber > INT16_MAX) return false;
            if (parsedNumber < INT16_MIN) return false;
            data.i16 = static_cast<int16_t>(parsedNumber);
            break;
        case E_WordSizes::U32:
            if (parsedNumber > INT32_MAX) return false;
            if (parsedNumber < INT32_MIN) return false;
            data.i32 = static_cast<int32_t>(parsedNumber);
            break;
        case E_WordSizes::U64:
            data.i64 = parsedNumber;
            break;
    }

    return pos == textStd.length();
}


// NOTE(Max): I am not sure what the best way is to both keep down code 
// reproduction and maintain readability. The dataChangedIntoSignedInt pair 
// could be a singed and unsigned version (current), or a templated function or 
// a capturing lambda (with container taking a std::function). 
CPP_LOCAL_FUN bool
dataChangedIntoUnsignedInt(
        const QString &text,
        DataModel *dataModel,
        Number &data,
        int base
) {
    auto textStd = text.toStdString();
    std::size_t pos = 0;

    if (textStd.length() == 0) {
        dataModel->setNumberEmpty(true);
        data = Number();
        return true;
    }

    // Remove any prefixes.
    if (base == 2) {
        textStd = repper::Utils::removeFormatPrefix(textStd, 2);
    }
    if (base == 16) {
        textStd = repper::Utils::removeFormatPrefix(textStd, 16);
    }


    unsigned long long int parsedNumber = 0;
    try {
        parsedNumber = std::stoull(textStd, &pos, base);
    }
    catch(std::invalid_argument const& ex) {
        invalidArgumentError(ex, dataModel);
        return false;
    }
    catch(std::out_of_range const& ex) {
        outOfRangeError(ex, dataModel);
        return false;
    }

    switch (dataModel->getWordSize()) {
        case E_WordSizes::U8:
            if (parsedNumber > UINT8_MAX) return false;
            data.u8 = static_cast<uint8_t>(parsedNumber);
            break;
        case E_WordSizes::U16:
            if (parsedNumber > UINT16_MAX) return false;
            data.u16 = static_cast<uint16_t>(parsedNumber);
            break;
        case E_WordSizes::U32:
            if (parsedNumber > UINT32_MAX) return false;
            data.u32 = static_cast<uint32_t>(parsedNumber);
            break;
        case E_WordSizes::U64:
            data.u64 = static_cast<uint64_t>(parsedNumber);
            break;
    }

    return pos == textStd.length();
}


// =============================================================================
// ===== Dec Singed ============================================================

CPP_LOCAL_FUN void
signedDecTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    std::cout << "Dec, signed, string changed: " << text.toStdString() << std::endl;

    Number newInt;
    bool processingSuccessful = dataChangedIntoSignedInt(
            text, dataModel, newInt
    );

    if (processingSuccessful) {
        dataModel->setData(newInt, E_FieldTypes::DEC_SIGNED);
    } else {
        dataModel->setUpdateState(
                E_FieldTypes::DEC_SIGNED, E_DataUpdateErrors::Generic
        );
    }

    dataModel->setUpdateSuccessfully(processingSuccessful);
}


CPP_LOCAL_FUN void
dataChangedSignedDec(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == E_FieldTypes::DEC_SIGNED) {
        return;
    }

    if (!dataModel->isUpdateSuccessful()) {
        editField->setText("Invalid");
        return;
    }

    QString displayString = "";

    if (!dataModel->isNumberEmpty()) {
        Number number = dataModel->getData();
        E_WordSizes wordSize = dataModel->getWordSize();

        switch (wordSize) {
            case E_WordSizes::U8: displayString = QString::number(number.i8, 10); break;
            case E_WordSizes::U16: displayString = QString::number(number.i16, 10); break;
            case E_WordSizes::U32: displayString = QString::number(number.i32, 10); break;
            case E_WordSizes::U64: displayString = QString::number(number.i64, 10); break;
        }
    }
    
    editField->setText(displayString);
}


GenericEditField *
EditFields::makeSignedDecEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&signedDecTextChanged);
    editField->setDataChangedFunction(&dataChangedSignedDec);

    return editField;
}


// =============================================================================
// ===== Dec Unsigned ==========================================================

CPP_LOCAL_FUN void
unsignedDecTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    std::cout << "Dec, unsigned, string changed: " << text.toStdString() << std::endl;

    Number newInt;
    bool processingSuccessful = dataChangedIntoUnsignedInt(
            text, dataModel, newInt, 10
    );

    if (processingSuccessful) {
        dataModel->setData(newInt, E_FieldTypes::DEC_UNSIGNED);
    } else {
        dataModel->setUpdateState(
                E_FieldTypes::DEC_UNSIGNED, E_DataUpdateErrors::Generic
        );
    }

    dataModel->setUpdateSuccessfully(processingSuccessful);
}


CPP_LOCAL_FUN void
dataChangedUnsignedDec(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == E_FieldTypes::DEC_UNSIGNED) {
        return;
    }

    if (!dataModel->isUpdateSuccessful()) {
        editField->setText("Invalid");
        return;
    }

    QString displayString = "";

    if (!dataModel->isNumberEmpty()) {
        Number number = dataModel->getData();
        E_WordSizes wordSize = dataModel->getWordSize();

//        std::string temp;
//        switch (wordSize) {
//            case E_WordSizes::U8: temp = std::to_string(number.u8); break;
//            case E_WordSizes::U16: temp = std::to_string(number.u16); break;
//            case E_WordSizes::U32: temp = std::to_string(number.u32); break;
//            case E_WordSizes::U64: temp = std::to_string(number.u64); break;
//        }
//
//        displayString = QString::fromStdString(temp);

        switch (wordSize) {
            case E_WordSizes::U8: displayString = QString::number(number.u8); break;
            case E_WordSizes::U16: displayString = QString::number(number.u16); break;
            case E_WordSizes::U32: displayString = QString::number(number.u32); break;
            case E_WordSizes::U64: displayString = QString::number(number.u64); break;
        }
    }

    editField->setText(displayString);
}


GenericEditField *
EditFields::makeUnsignedDecEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&unsignedDecTextChanged);
    editField->setDataChangedFunction(&dataChangedUnsignedDec);

    return editField;
}


// =============================================================================
// ===== Hex ===================================================================

CPP_LOCAL_FUN void
hexTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    std::cout << "Hex string changed: " << text.toStdString() << std::endl;

    Number newInt;
    bool processingSuccessful = dataChangedIntoUnsignedInt(
            text, dataModel, newInt, 16
    );

    if (processingSuccessful) {
        dataModel->setData(newInt, E_FieldTypes::HEX);
    } else {
        dataModel->setUpdateState(
                E_FieldTypes::HEX, E_DataUpdateErrors::Generic
        );
    }

    dataModel->setUpdateSuccessfully(processingSuccessful);
}


CPP_LOCAL_FUN void
dataChangedHex(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == E_FieldTypes::HEX) {
        return;
    }

    if (!dataModel->isUpdateSuccessful()) {
        editField->setText("Invalid");
        return;
    }

    QString displayString = "";

    if (!dataModel->isNumberEmpty()) {
        Number newNumber = dataModel->getData();
        E_WordSizes wordSize = dataModel->getWordSize();

        switch (wordSize) {
            case E_WordSizes::U8: displayString = QString::number(newNumber.u8, 16); break;
            case E_WordSizes::U16: displayString = QString::number(newNumber.u16, 16); break;
            case E_WordSizes::U32: displayString = QString::number(newNumber.u32, 16); break;
            case E_WordSizes::U64: displayString = QString::number(newNumber.u64, 16); break;
        }

        displayString = "0x" + displayString;
    }

    editField->setText(displayString);
}


GenericEditField *
EditFields::makeHexEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&hexTextChanged);
    editField->setDataChangedFunction(&dataChangedHex);

    return editField;
}


// =============================================================================
// ===== Bin ===================================================================

CPP_LOCAL_FUN void
binTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    std::cout << "Bin string changed: " << text.toStdString() << std::endl;

    Number newInt;
    bool processingSuccessful = dataChangedIntoUnsignedInt(
            text, dataModel, newInt, 2
    );

    if (processingSuccessful) {
        dataModel->setData(newInt, E_FieldTypes::BIN);
    } else {
        dataModel->setUpdateState(
                E_FieldTypes::BIN, E_DataUpdateErrors::Generic
        );
    }

    dataModel->setUpdateSuccessfully(processingSuccessful);
}


CPP_LOCAL_FUN void
dataChangedBin(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == E_FieldTypes::BIN) {
        return;
    }

    if (!dataModel->isUpdateSuccessful()) {
        editField->setText("Invalid");
        return;
    }

    QString displayString = "";

    if (!dataModel->isNumberEmpty()) {
        Number newNumber = dataModel->getData();
        E_WordSizes wordSize = dataModel->getWordSize();

        switch (wordSize) {
            case E_WordSizes::U8: displayString = QString::number(newNumber.u8, 2); break;
            case E_WordSizes::U16: displayString = QString::number(newNumber.u16, 2); break;
            case E_WordSizes::U32: displayString = QString::number(newNumber.u32, 2); break;
            case E_WordSizes::U64: displayString = QString::number(newNumber.u64, 2); break;
        }

        displayString = "0b" + displayString;
    }

    editField->setText(displayString);
}


GenericEditField *
EditFields::makeBinEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&binTextChanged);
    editField->setDataChangedFunction(&dataChangedBin);

    return editField;
}


// =============================================================================
// ===== Float =================================================================

CPP_LOCAL_FUN bool
floatChangedIntro(
        const std::string& textStd,
        DataModel *dataModel,
        Number *data
) {
    std::cout << "Float string changed: " << textStd << std::endl;

    if (textStd.length() == 0) {
        dataModel->setNumberEmpty(true);
        *data = Number();
        return true;
    }

    std::size_t pos = 0;
    try {
        E_WordSizes wordSize = dataModel->getWordSize();
        switch (wordSize) {
            case E_WordSizes::U64: data->f64 = std::stod(textStd, &pos); break;
            case E_WordSizes::U32: data->f32 = std::stof(textStd, &pos); break;
            default: throw std::runtime_error(
                    "Can't use float unless in 32 or 64 bit mode."
            );
        }
    }
    catch(std::invalid_argument const& ex) {
        invalidArgumentError(ex, dataModel);
        return false;
    }
    catch(std::out_of_range const& ex) {
        outOfRangeError(ex, dataModel);
        return false;
    }

    return pos == textStd.length();
}


CPP_LOCAL_FUN void
floatTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    const auto textStd = text.toStdString();
    Number newFloat = Number();

    bool goodParse = floatChangedIntro(textStd, dataModel, &newFloat);

    if (goodParse) {
        dataModel->setData(newFloat, E_FieldTypes::FLOAT);
    } else {
        dataModel->setUpdateState(
                E_FieldTypes::FLOAT, E_DataUpdateErrors::Generic
        );
    }

    dataModel->setUpdateSuccessfully(goodParse);
}


CPP_LOCAL_FUN void
dataChangedFloat(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == E_FieldTypes::FLOAT) {
        return;
    }

    if (!dataModel->isUpdateSuccessful()) {
        editField->setText("Invalid");
        return;
    }


    Number data = dataModel->getData();
    E_WordSizes size = dataModel->getWordSize();
    QString qString;

    switch (size) {
        case E_WordSizes::U8:
            editField->setText("Not Implemented For 8 Bits.");
            editField->setDisabled(true);
            break;
        case E_WordSizes::U16:
            editField->setText("Not Implemented For 16 Bits.");
            editField->setDisabled(true);
            break;
        case E_WordSizes::U32:
            qString = (dataModel->isNumberEmpty())
                      ? "" : QString::number(data.f32);
            editField->setText(qString);
            editField->setDisabled(false);
            break;
        case E_WordSizes::U64:
            qString = (dataModel->isNumberEmpty())
                      ? "" : QString::number(data.f64);
            editField->setText(qString);
            editField->setDisabled(false);
            break;
    }
}


GenericEditField *
EditFields::makeFloatEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&floatTextChanged);
    editField->setDataChangedFunction(&dataChangedFloat);

    return editField;
}
