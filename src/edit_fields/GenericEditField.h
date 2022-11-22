//
// Created by max on 12/06/22.
//

#ifndef NUMREPRESENTATION_GENERICEDITFIELD_H
#define NUMREPRESENTATION_GENERICEDITFIELD_H


#include <QLineEdit>

#include "../data_model/DataModel.h"



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


public:
    GenericEditField(
            QWidget *parent,
            DataModel *dataModel
    ) :
            QLineEdit(parent),
            dataModel_(dataModel),
            textChanged_(nullptr),
            dataChanged_(nullptr)
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
    }


public:
    void setTextChangedFunction(TextChangedFunction textChangedFunction) {
        textChanged_ = textChangedFunction;
    }

    void setDataChangedFunction(DataChangedFunction dataChangedFunction) {
        dataChanged_ = dataChangedFunction;
    }


private slots:
    void generalTextChanged(const QString &text) {
        assert(textChanged_);
        dataModel_->setNumberEmpty(text.isEmpty());
        textChanged_(text, dataModel_);
    };

    void generalDataModelUpdated() {
        assert(dataChanged_);
        dataChanged_(this, dataModel_);
    }

};


#endif //NUMREPRESENTATION_GENERICEDITFIELD_H
