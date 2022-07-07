//
// Created by max on 12/06/22.
//

#include <sstream>

#include "EditFields.h"


#define INVALID_ARGUMENT_ERROR \
    std::cout << "std::invalid_argument::what(): " \
              << ex.what() \
              << std::endl; \
    dataModel->setUpdateSuccessfully(false); \
    return;

#define OUT_OF_RANGE_ERROR \
    std::cout << "std::out_of_range::what(): " \
              << ex.what() \
              << std::endl; \
    dataModel->setUpdateSuccessfully(false); \
    return;


// =============================================================================
// ===== Dec ==================================================================

void
decTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    const auto textStd = text.toStdString();
    std::size_t pos = 0;

    std::cout << "Dec string changed: " << text.toStdString() << std::endl;
    Number data;

    try {
        data.i32 = std::stoi(textStd, &pos, 10);
    }
    catch(std::invalid_argument const& ex) {
        INVALID_ARGUMENT_ERROR
    }
    catch(std::out_of_range const& ex) {
        OUT_OF_RANGE_ERROR
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return;
    }


    dataModel->setData(data, FieldTypes::DEC);
    dataModel->setUpdateSuccessfully(true);
}


void
dataChangedDec(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == FieldTypes::DEC) {
        return;
    }

    if (!dataModel->isUpdateSuccessful()) {
        editField->setText("Invalid");
        return;
    }

    Number newNumber = dataModel->getData();
    editField->setText(QString::number(newNumber.i32, 10));
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
    const auto textStd = text.toStdString();
    std::size_t pos = 0;

    std::cout << "Hex string changed: " << text.toStdString() << std::endl;
    Number newInt;

    try {
        newInt.i32 = std::stoi(textStd, &pos, 16);
    }
    catch(std::invalid_argument const& ex) {
        INVALID_ARGUMENT_ERROR
    }
    catch(std::out_of_range const& ex) {
        OUT_OF_RANGE_ERROR
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return;
    }

    dataModel->setData(newInt,FieldTypes::HEX);
    dataModel->setUpdateSuccessfully(true);
}


void
dataChangedHex(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == FieldTypes::HEX) {
        return;
    }

    if (!dataModel->isUpdateSuccessful()) {
        editField->setText("Invalid");
        return;
    }

    Number newNumber = dataModel->getData();
    QString sign = "";

    if (newNumber.i32 < 0) {
        sign = "-";
    }

    editField->setText(sign + "0x" + QString::number(abs(newNumber.i32), 16));
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
    const auto textStd = text.toStdString();
    std::size_t pos = 0;

    std::cout << "Bin string changed: " << text.toStdString() << std::endl;
    Number newInt;

    try {
        newInt.i32 = std::stoi(textStd, &pos, 2);
    }
    catch(std::invalid_argument const& ex) {
        INVALID_ARGUMENT_ERROR
    }
    catch(std::out_of_range const& ex) {
        OUT_OF_RANGE_ERROR
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return;
    }

    dataModel->setData(newInt, FieldTypes::BIN);
    dataModel->setUpdateSuccessfully(true);
}


void
dataChangedBin(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == FieldTypes::BIN) {
        return;
    }

    if (!dataModel->isUpdateSuccessful()) {
        editField->setText("Invalid");
        return;
    }

    Number data = dataModel->getData();
    editField->setText("0b" + QString::number(data.i32, 2));
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

void
floatTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    const auto textStd = text.toStdString();
    std::size_t pos = 0;

    std::cout << "Float string changed: "
              << text.toStdString()
              << std::endl;

    Number newFloat;

    try {
        E_WordSizes size = dataModel->getWordSize();
        if (size == E_WordSizes::U32) {
            newFloat.f32 = std::stof(textStd, &pos);
        } else if (size == E_WordSizes::U64) {
            newFloat.f64 = std::stod(textStd, &pos);
        } else {
            throw std::runtime_error("Can't use float unless in 32 or 64 bit "
                                     "mode.");
        }
    }
    catch(std::invalid_argument const& ex) {
        INVALID_ARGUMENT_ERROR
    }
    catch(std::out_of_range const& ex) {
        OUT_OF_RANGE_ERROR
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return;
    }

    dataModel->setData(newFloat, FieldTypes::FLOAT);
    dataModel->setUpdateSuccessfully(true);
}


void
dataChangedFloat(
        QLineEdit *editField,
        DataModel *dataModel
) {
    if (dataModel->getUpdatingFieldType() == FieldTypes::FLOAT) {
        return;
    }

    if (!dataModel->isUpdateSuccessful()) {
        editField->setText("Invalid");
        return;
    }

    Number data = dataModel->getData();
    E_WordSizes size = dataModel->getWordSize();

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
            editField->setText(QString::number(data.f32));
            editField->setDisabled(false);
            break;
        case E_WordSizes::U64:
            editField->setText(QString::number(data.f64));
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
