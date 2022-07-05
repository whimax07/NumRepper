//
// Created by max on 05/07/22.
//

#ifndef NUMREPRESENTATION_WORDSIZERADIOBUTTON_H
#define NUMREPRESENTATION_WORDSIZERADIOBUTTON_H


#include <QRadioButton>
#include "WordSizes.h"
#include "../data_modle/DataModel.h"

class WordSizeRadioButton : public QRadioButton {
    Q_OBJECT

private:
    DataModel *dataModel_;

    WordSizes wordSize_;


public:
    WordSizeRadioButton(
            const QString &text,
            QWidget *parent,
            DataModel *dataModel,
            WordSizes wordSize
    ) : QRadioButton(text, parent), dataModel_(dataModel), wordSize_(wordSize)
    {  }


public slots:
    void updateDataModel(bool checked) {
        if (checked) {
            dataModel_->changeWordSize(wordSize_);
        }
    }

};


#endif //NUMREPRESENTATION_WORDSIZERADIOBUTTON_H