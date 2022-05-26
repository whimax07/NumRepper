//
// Created by max on 26/05/22.
//

#ifndef NUMREPRESENTATION_FLOATEDIT_H
#define NUMREPRESENTATION_FLOATEDIT_H


#include <QLineEdit>

#include "../data_modle/DataModel.h"


class FloatEdit : public QLineEdit {
Q_OBJECT

private:
    DataModel *_dataModel;


public:
    FloatEdit(QWidget *parent, DataModel *dataModel) :
            QLineEdit(parent), _dataModel(dataModel) {
        connect(
                this, &FloatEdit::textEdited,
                this, &FloatEdit::floatTextChanged
        );
    }


private slots:
    void floatTextChanged(const QString &text) {
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
            return;
        }
        catch(std::out_of_range const& ex) {
            std::cout << "std::out_of_range::what(): "
                      << ex.what()
                      << std::endl;
            return;
        }

        if (pos != textStd.length()) {
            return;
        }

        _dataModel->setModelData(
                (uint64_t) *(uint32_t *) &newFloat,
                FieldTypes::FLOAT
        );
    }

};


#endif //NUMREPRESENTATION_FLOATEDIT_H
