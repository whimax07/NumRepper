//
// Created by max on 12/06/22.
//

#include <sstream>

#include "EditFields.h"
#include "../utils/Utils.h"


#define INVALID_ARGUMENT_ERROR \
    std::cout << "std::invalid_argument::what(): " \
              << ex.what() \
              << std::endl; \
    dataModel->setUpdateSuccessfully(false); \

#define OUT_OF_RANGE_ERROR \
    std::cout << "std::out_of_range::what(): " \
              << ex.what() \
              << std::endl; \
    dataModel->setUpdateSuccessfully(false); \



// =============================================================================
// ===== Utils =================================================================

bool
dataChangedIntoInt(
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
    textStd = repper::Utils::removeFormatPrefix(textStd, 2);
    textStd = repper::Utils::removeFormatPrefix(textStd, 16);


    try {
        switch (dataModel->getWordSize()) {
            case E_WordSizes::U8:
                data.u8 = static_cast<uint8_t>(std::stoull(textStd, &pos, base));
                break;
            case E_WordSizes::I16:
                data.i16 = static_cast<int16_t>(std::stoi(textStd, &pos, base));
                break;
            case E_WordSizes::I32:
                data.i32 = std::stoi(textStd, &pos, base);
                break;
            case E_WordSizes::I64:
                data.i64 = static_cast<int64_t>(std::stoll(textStd, &pos, base));
                break;
        }
    }
    catch(std::invalid_argument const& ex) {
        INVALID_ARGUMENT_ERROR
        return false;
    }
    catch(std::out_of_range const& ex) {
        OUT_OF_RANGE_ERROR
        return false;
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return false;
    }

    return true;
}


// =============================================================================
// ===== Dec ===================================================================

void
decTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    std::cout << "Dec string changed: " << text.toStdString() << std::endl;

    Number newInt;
    bool processingSuccessful = dataChangedIntoInt(
            text, dataModel, newInt, 10
    );
    if (!processingSuccessful) return;

    dataModel->setData(newInt, E_FieldTypes::DEC);
    dataModel->setUpdateSuccessfully(true);
}


void
dataChangedDec(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == E_FieldTypes::DEC) {
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
            case E_WordSizes::U8: displayString = QString::number(number.u8, 10); break;
            case E_WordSizes::I16: displayString = QString::number(number.i16, 10); break;
            case E_WordSizes::I32: displayString = QString::number(number.i32, 10); break;
            case E_WordSizes::I64: displayString = QString::number(number.i64, 10); break;
        }
    }
    
    editField->setText(displayString);
}


GenericEditField *
EditFields::makeDecEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&decTextChanged);
    editField->setDataChangedFunction(&dataChangedDec);

    return editField;
}


// =============================================================================
// ===== Hex ===================================================================

void
hexTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    std::cout << "Hex string changed: " << text.toStdString() << std::endl;

    Number newInt;
    bool processingSuccessful = dataChangedIntoInt(
            text, dataModel, newInt, 16
    );
    if (!processingSuccessful) return;

    dataModel->setData(newInt, E_FieldTypes::HEX);
    dataModel->setUpdateSuccessfully(true);
}


void
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
    QString sign = "";

    if (!dataModel->isNumberEmpty()) {
        Number newNumber = dataModel->getData();
        E_WordSizes wordSize = dataModel->getWordSize();

        switch (wordSize) {
            case E_WordSizes::I64: if (newNumber.i64 < 0) sign = "-"; break;
            case E_WordSizes::I32: if (newNumber.i32 < 0) sign = "-"; break;
            case E_WordSizes::I16: if (newNumber.i16 < 0) sign = "-"; break;
            default: break;
        }

        switch (wordSize) {
            case E_WordSizes::U8: displayString = QString::number(newNumber.u8, 16); break;
            case E_WordSizes::I16: displayString = QString::number(newNumber.i16, 16); break;
            case E_WordSizes::I32: displayString = QString::number(newNumber.i32, 16); break;
            case E_WordSizes::I64: displayString = QString::number(newNumber.i64, 16); break;
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

void
binTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    std::cout << "Bin string changed: " << text.toStdString() << std::endl;

    Number newInt;
    bool processingSuccessful = dataChangedIntoInt(
            text, dataModel, newInt, 2
    );
    if (!processingSuccessful) return;

    dataModel->setData(newInt, E_FieldTypes::BIN);
    dataModel->setUpdateSuccessfully(true);
}


void
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
            case E_WordSizes::I16: displayString = QString::number(newNumber.u16, 2); break;
            case E_WordSizes::I32: displayString = QString::number(newNumber.u32, 2); break;
            case E_WordSizes::I64: displayString = QString::number(newNumber.u64, 2); break;
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

bool
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
            case E_WordSizes::I64: data->f64 = std::stod(textStd, &pos); break;
            case E_WordSizes::I32: data->f32 = std::stof(textStd, &pos); break;
            default: throw std::runtime_error(
                    "Can't use float unless in 32 or 64 bit mode."
            );
        }
    }
    catch(std::invalid_argument const& ex) {
        INVALID_ARGUMENT_ERROR
        return false;
    }
    catch(std::out_of_range const& ex) {
        OUT_OF_RANGE_ERROR
        return false;
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return false;
    }

    return true;
}


void
floatTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    const auto textStd = text.toStdString();
    Number newFloat = Number();

    bool goodParse = floatChangedIntro(textStd, dataModel, &newFloat);
    if (!goodParse) return;

    dataModel->setData(newFloat, E_FieldTypes::FLOAT);
    dataModel->setUpdateSuccessfully(true);
}


void
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
        case E_WordSizes::I16:
            editField->setText("Not Implemented For 16 Bits.");
            editField->setDisabled(true);
            break;
        case E_WordSizes::I32:
            qString = (dataModel->isNumberEmpty())
                      ? "" : QString::number(data.f32);
            editField->setText(qString);
            editField->setDisabled(false);
            break;
        case E_WordSizes::I64:
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
