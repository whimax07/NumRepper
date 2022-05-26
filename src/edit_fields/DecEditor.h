//
// Created by max on 24/05/22.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#ifndef NUMREPRESENTATION_DECEDITOR_H
#define NUMREPRESENTATION_DECEDITOR_H


#include <iostream>

#include <QLineEdit>

#include "../data_modle/DataModel.h"


class DecEditor : public QLineEdit {
Q_OBJECT

private:
    DataModel *_dataModel;


public:
    DecEditor(QWidget *parent, DataModel *dataModel) :
            QLineEdit(parent), _dataModel(dataModel) {
        connect(
                this, &DecEditor::textEdited,
                this, &DecEditor::decTextChanged
        );

        connect(
                _dataModel, &DataModel::dataUpdated,
                this, &DecEditor::numberUpdated
        );
    }


private slots:
    void decTextChanged(const QString &text) {
        const auto textStd = text.toStdString();
        std::size_t pos = 0;

        std::cout << "Dec string changed: " << text.toStdString() << std::endl;
        uint64_t newInt;

        try {
            newInt = std::stoi(textStd, &pos, 10);
        }
        catch(std::invalid_argument const& ex) {
            std::cout << "std::invalid_argument::what(): " << ex.what()
                      << std::endl;
            return;
        }
        catch(std::out_of_range const& ex) {
            std::cout << "std::out_of_range::what(): " << ex.what()
                      << std::endl;
            return;
        }

        if (pos != textStd.length()) {
            return;
        }

        _dataModel->setModelData(
                *(uint64_t *) &newInt,
                FieldTypes::DEC
        );
    }

    void numberUpdated(uint64_t data, FieldTypes source) {
        if (source == FieldTypes::DEC) {
            return;
        }

        int newData = *(int *) &data;
        setText(QString::number(newData, 10));
    }

};


#endif //NUMREPRESENTATION_DECEDITOR_H

#pragma clang diagnostic pop