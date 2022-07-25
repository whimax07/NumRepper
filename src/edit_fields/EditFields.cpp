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

#define OUT_OF_RANGE_ERROR \
    std::cout << "std::out_of_range::what(): " \
              << ex.what() \
              << std::endl; \
    dataModel->setUpdateSuccessfully(false); \



// =============================================================================
// ===== Utils =================================================================

bool
dataChangedIntroInt(
        const QString &text,
        DataModel *dataModel,
        Number *data,
        int base
) {
    const auto textStd = text.toStdString();
    std::size_t pos = 0;

    if (textStd.length() == 0) {
        dataModel->notifyEmptyField();
        return false;
    }

    try {
        (*data).i32 = std::stoi(textStd, &pos, base);
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
updateTextFieldInt(
        QLineEdit *editField,
        DataModel *dataModel,
        int base
) {
    Number data = dataModel->getData();
    E_WordSizes size = dataModel->getWordSize();

    switch (size) {
        case E_WordSizes::U8:
            editField->setText(QString::number(data.u8, base));
            editField->setDisabled(false);
            break;
        case E_WordSizes::U16:
            editField->setText(QString::number(data.i16, base));
            editField->setDisabled(false);
            break;
        case E_WordSizes::U32:
            editField->setText(QString::number(data.i32, base));
            editField->setDisabled(false);
            break;
        case E_WordSizes::U64:
            editField->setText(QString::number(data.i64, base));
            editField->setDisabled(false);
            break;
    }
}


QString
createQStringFromInt(
        Number number,
        E_WordSizes wordSize,
        int base
) {
    switch (wordSize) {
        case E_WordSizes::U8: return QString::number(number.u8, base);
        case E_WordSizes::U16: return QString::number(number.u16, base);
        case E_WordSizes::U32: return QString::number(number.u32, base);
        case E_WordSizes::U64: return QString::number(number.u64, base);
    }
}


void
clearField(
        QLineEdit *editField,
        DataModel *dataModel
) {
    editField->setText("");
}


// =============================================================================
// ===== Dec ===================================================================

void
decTextChanged(
        const QString &text,
        DataModel *dataModel
) {
    std::cout << "Dec string changed: " << text.toStdString() << std::endl;

    Number data;
    bool processingSuccessful = dataChangedIntroInt(text, dataModel, &data, 10);
    if (!processingSuccessful) return;

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

    const QString &qStringFromNumber = createQStringFromInt(
            newNumber,
            dataModel->getWordSize(),
            10
    );

    editField->setText(qStringFromNumber);
}


GenericEditField *
EditFields::makeDecEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&decTextChanged);
    editField->setDataChangedFunction(&dataChangedDec);
    editField->setDataSizeChangedFunction(
            [] (QLineEdit *editField, DataModel *dataModel) -> void {
                updateTextFieldInt(editField, dataModel, 10);
            }
    );
    editField->setProcessEmptyField(&clearField);

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
    bool processingSuccessful = dataChangedIntroInt(text, dataModel, &newInt,
                                                    16);
    if (!processingSuccessful) return;

    dataModel->setData(newInt, FieldTypes::HEX);
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

    const QString &qStringFromNumber = createQStringFromInt(
            newNumber,
            dataModel->getWordSize(),
            16
    );

    editField->setText(sign + "0x" + qStringFromNumber);
}


GenericEditField *
EditFields::makeHexEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&hexTextChanged);
    editField->setDataChangedFunction(&dataChangedHex);
    editField->setDataSizeChangedFunction(
            [] (QLineEdit *editField, DataModel *dataModel) -> void {
                updateTextFieldInt(editField, dataModel, 16);
            }
    );
    editField->setProcessEmptyField(&clearField);

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
    bool processingSuccessful = dataChangedIntroInt(text, dataModel, &newInt,
                                                    10);
    if (!processingSuccessful) return;

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

    const QString &qStringFromNumber = createQStringFromInt(
            data,
            dataModel->getWordSize(),
            2
    );

    editField->setText("0b" + qStringFromNumber);
}


GenericEditField *
EditFields::makeBinEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&binTextChanged);
    editField->setDataChangedFunction(&dataChangedBin);
    editField->setDataSizeChangedFunction(
            [] (QLineEdit *editField, DataModel *dataModel) -> void {
                updateTextFieldInt(editField, dataModel, 2);
            }
    );
    editField->setProcessEmptyField(&clearField);

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

    if (textStd.length() == 0) {
        dataModel->processEmptyField();
        return;
    }

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
        return;
    }
    catch(std::out_of_range const& ex) {
        OUT_OF_RANGE_ERROR
        return;
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return;
    }

    dataModel->setData(newFloat, FieldTypes::FLOAT);
    dataModel->setUpdateSuccessfully(true);
}


void
updateTextFieldFloat(
        QLineEdit *editField,
        DataModel *dataModel
) {
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


void
processEmptyFieldFloat(
        QLineEdit *editField,
        DataModel *dataModel
) {
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
        case E_WordSizes::U64:
            editField->setText("");
            editField->setDisabled(false);
            break;
    }
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

    updateTextFieldFloat(editField, dataModel);
}


GenericEditField *
EditFields::makeFloatEditor(
        QWidget *parent,
        DataModel *dataModel
) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&floatTextChanged);
    editField->setDataChangedFunction(&dataChangedFloat);
    editField->setDataSizeChangedFunction(&updateTextFieldFloat);
    editField->setProcessEmptyField(&processEmptyFieldFloat);

    return editField;
}
