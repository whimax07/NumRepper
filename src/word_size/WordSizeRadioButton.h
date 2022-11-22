//
// Created by max on 05/07/22.
//

#ifndef NUMREPRESENTATION_WORDSIZERADIOBUTTON_H
#define NUMREPRESENTATION_WORDSIZERADIOBUTTON_H


#include <QRadioButton>
#include "E_WordSizes.h"
#include "../data_model/DataModel.h"

class WordSizeRadioButton : public QRadioButton {
    Q_OBJECT

private:
    DataModel *dataModel_;

    E_WordSizes wordSize_;


public:
    WordSizeRadioButton(
            const QString &text,
            QWidget *parent,
            DataModel *dataModel,
            E_WordSizes wordSize
    ) : QRadioButton(text, parent), dataModel_(dataModel), wordSize_(wordSize)
    {  }


public slots:
    void updateDataModel(bool checked) {
        if (checked) {
            dataModel_->setWordSize(wordSize_);
        }
    }

};


#endif //NUMREPRESENTATION_WORDSIZERADIOBUTTON_H
