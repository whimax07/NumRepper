//
// Created by max on 24/05/22.
//

#ifndef NUMREPRESENTATION_HEXEDITOR_H
#define NUMREPRESENTATION_HEXEDITOR_H


#include <QLineEdit>

#include "../data_modle/DataModel.h"


class HexEditor : public QLineEdit {
Q_OBJECT

private:
    DataModel *_dataModel;


public:
    HexEditor(QWidget *parent, DataModel *dataModel) :
            QLineEdit(parent), _dataModel(dataModel) {
        connect(
                this, &HexEditor::textEdited,
                this, &HexEditor::decTextChanged
        );

        connect(
                _dataModel, &DataModel::dataUpdated,
                this, &HexEditor::numberUpdated
        );
    }


private slots:
    void decTextChanged(const QString &text) {
        const auto textStd = text.toStdString();
        std::size_t pos = 0;

        std::cout << "Hex string changed: " << text.toStdString() << std::endl;
        uint64_t newInt;

        try {
            newInt = std::stoi(textStd, &pos, 16);
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
                FieldTypes::HEX
        );
    }

    void numberUpdated(uint64_t data, FieldTypes source) {
        if (source == FieldTypes::HEX) {
            return;
        }

        int newData = *(int *) &data;
        QString sign = "";

        if (newData < 0) {
            sign = "-";
        }

        setText(sign + "0x" + QString::number(abs(newData), 16));
    }

};


#endif //NUMREPRESENTATION_HEXEDITOR_H
