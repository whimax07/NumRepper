//
// Created by max on 12/06/22.
//

#include <sstream>

#include "EditFields.h"


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
    uint64_t newInt;

    try {
        newInt = std::stoi(textStd, &pos, 10);
    }
    catch(std::invalid_argument const& ex) {
        std::cout << "std::invalid_argument::what(): "
                  << ex.what()
                  << std::endl;

        dataModel->setUpdateSuccessfully(false);
        return;
    }
    catch(std::out_of_range const& ex) {
        std::cout << "std::out_of_range::what(): "
                  << ex.what()
                  << std::endl;

        dataModel->setUpdateSuccessfully(false);
        return;
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return;
    }

    dataModel->setModelData(
            *(uint64_t *) &newInt,
            FieldTypes::DEC
    );
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

    uint64_t data = dataModel->getModelData();
    int newData = *(int *) &data;
    editField->setText(QString::number(newData, 10));
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
    uint64_t newInt;

    try {
        newInt = std::stoi(textStd, &pos, 16);
    }
    catch(std::invalid_argument const& ex) {
        std::cout << "std::invalid_argument::what(): "
                  << ex.what()
                  << std::endl;
        dataModel->setUpdateSuccessfully(false);
        return;
    }
    catch(std::out_of_range const& ex) {
        std::cout << "std::out_of_range::what(): "
                  << ex.what()
                  << std::endl;
        dataModel->setUpdateSuccessfully(false);
        return;
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return;
    }

    dataModel->setModelData(
            *(uint64_t *) &newInt,
            FieldTypes::HEX
    );
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

    uint64_t data = dataModel->getModelData();
    int newData = *(int *) &data;
    QString sign = "";

    if (newData < 0) {
        sign = "-";
    }

    editField->setText(sign + "0x" + QString::number(abs(newData), 16));
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

    float newFloat;

    try {
        newFloat = std::stof(textStd, &pos);
    }
    catch(std::invalid_argument const& ex) {
        std::cout << "std::invalid_argument::what(): "
                  << ex.what()
                  << std::endl;

        dataModel->setUpdateSuccessfully(false);
        return;
    }
    catch(std::out_of_range const& ex) {
        std::cout << "std::out_of_range::what(): "
                  << ex.what()
                  << std::endl;

        dataModel->setUpdateSuccessfully(false);
        return;
    }

    if (pos != textStd.length()) {
        dataModel->setUpdateSuccessfully(false);
        return;
    }

    dataModel->setModelData(
            (uint64_t) *(uint32_t *) &newFloat,
            FieldTypes::FLOAT
    );
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

    uint64_t data = dataModel->getModelData();
    float newData = *(float *) &data;

    std::ostringstream ss;
    ss << newData;
    std::string s = ss.str();
    editField->setText(QString::fromStdString(s));
}


GenericEditField *
EditFields::makeFloatEditor(QWidget *parent, DataModel *dataModel) {
    auto editField = new GenericEditField(parent, dataModel);

    editField->setTextChangedFunction(&floatTextChanged);
    editField->setDataChangedFunction(&dataChangedFloat);

    return editField;
}
