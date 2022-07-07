//
// Created by max on 12/06/22.
//

#ifndef NUMREPRESENTATION_GENERICEDITFIELD_H
#define NUMREPRESENTATION_GENERICEDITFIELD_H


#include <QLineEdit>

#include "../data_modle/DataModel.h"



using TextChangedFunction = void (*)(
        const QString &text,
        DataModel *dataModel
);

using DataChangedFunction = void (*)(
        QLineEdit *editField,
        DataModel *dataModel
);



class GenericEditField : public QLineEdit {
Q_OBJECT

private:
    DataModel *dataModel_;

    TextChangedFunction textChanged_;

    DataChangedFunction dataChanged_;

    DataChangedFunction dataSizeChanged_;

    DataChangedFunction processEmptyFieldFunction_;


public:
    GenericEditField(
            QWidget *parent,
            DataModel *dataModel
    ) :
            QLineEdit(parent),
            dataModel_(dataModel),
            textChanged_(nullptr),
            dataChanged_(nullptr),
            dataSizeChanged_(nullptr),
            processEmptyFieldFunction_(nullptr)
    {
        // Update the data model when the text changes.
        connect(
                this, &GenericEditField::textEdited,
                this, &GenericEditField::generalTextChanged
        );

        // Update the text when the data model changes.
        connect(
                dataModel_, &DataModel::generalDataUpdated,
                this, &GenericEditField::generalDataModelUpdated
        );

        // Update the text in the edit field when the data length is changed.
        connect(
                dataModel_, &DataModel::dataSizeChanged,
                this, &GenericEditField::generalDataSizeChanged
        );

        // Process a request to clear the field.
        connect(
                dataModel_, &DataModel::processEmptyField,
                this, &GenericEditField::processEmptyField
        );
    }

    void setTextChangedFunction(TextChangedFunction textChangedFunction) {
        textChanged_ = textChangedFunction;
    }

    void setDataChangedFunction(DataChangedFunction dataChangedFunction) {
        dataChanged_ = dataChangedFunction;
    }

    void setDataSizeChangedFunction(
            DataChangedFunction dataSizeChangedFunction) {
        dataSizeChanged_ = dataSizeChangedFunction;
    }

    void setProcessEmptyField(DataChangedFunction processEmptyFieldFunction) {
        processEmptyFieldFunction_ = processEmptyFieldFunction;
    }


private slots:
    void generalTextChanged(const QString &text) {
        assert(textChanged_);
        textChanged_(text, dataModel_);
    };

    void generalDataModelUpdated() {
        assert(dataChanged_);
        dataChanged_(this, dataModel_);
    }

    void generalDataSizeChanged() {
        if (dataSizeChanged_ == nullptr) return;
        assert(dataSizeChanged_);
        dataSizeChanged_(this, dataModel_);
    }

    void processEmptyField() {
        if (processEmptyFieldFunction_ == nullptr) return;
        assert(processEmptyFieldFunction_);
        processEmptyFieldFunction_(this, dataModel_);
    }

};


#endif //NUMREPRESENTATION_GENERICEDITFIELD_H
