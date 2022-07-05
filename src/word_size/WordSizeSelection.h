//
// Created by max on 05/07/22.
//

#ifndef NUMREPRESENTATION_WORDSIZESELECTION_H
#define NUMREPRESENTATION_WORDSIZESELECTION_H


#include <QWidget>
#include <QRadioButton>
#include <QHBoxLayout>
#include "../data_modle/DataModel.h"

class WordSizeSelection : public QWidget {
Q_OBJECT

private:
    DataModel *dataModel_;


public:
    WordSizeSelection(
            DataModel *dataModel
    ) : dataModel_{ dataModel_ } {
        makeAndPlaceButtons();
    }


private:
    void makeAndPlaceButtons() {
        auto layout = new QHBoxLayout(this);

        auto b64 = new QRadioButton("64 Bits",this);
        auto b32 = new QRadioButton("32 Bits" , this);
        auto b16 = new QRadioButton("16 Bits" , this);
        auto b8 = new QRadioButton("8 Bits", this);

        b32->setChecked(true);

        layout->addWidget(b64);
        layout->addWidget(b32);
        layout->addWidget(b16);
        layout->addWidget(b8);
    }

};


#endif //NUMREPRESENTATION_WORDSIZESELECTION_H
