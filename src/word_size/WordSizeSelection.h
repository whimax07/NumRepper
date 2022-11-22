//
// Created by max on 05/07/22.
//

#ifndef NUMREPRESENTATION_WORDSIZESELECTION_H
#define NUMREPRESENTATION_WORDSIZESELECTION_H


#include <QWidget>
#include <QRadioButton>
#include <QHBoxLayout>
#include "../data_modle/DataModel.h"
#include "WordSizeRadioButton.h"


class WordSizeSelection : public QWidget {
Q_OBJECT

private:
    DataModel *dataModel_;


public:
    explicit WordSizeSelection(DataModel *dataModel) : dataModel_(dataModel) {
        makeAndPlaceButtons();
    }


private:
    void makeAndPlaceButtons() {
        auto layout = new QHBoxLayout(this);

        makeAndPlaceButton(layout, "64 Bits", E_WordSizes::U64);

        auto b32 = makeAndPlaceButton(
                layout, "32 Bits", E_WordSizes::U32
        );
        b32->setChecked(true);

        makeAndPlaceButton(layout, "16 Bits", E_WordSizes::U16);

        makeAndPlaceButton(layout, "8 Bits", E_WordSizes::U8);
    }

    WordSizeRadioButton * makeAndPlaceButton(
            QHBoxLayout *layout,
            const QString& name,
            E_WordSizes size
    ) {
        auto button = new WordSizeRadioButton(
                name, this, dataModel_, size
        );

        connect(
                button, &WordSizeRadioButton::clicked,
                button, &WordSizeRadioButton::updateDataModel
        );

        layout->addWidget(button);

        return button;
    }

};



#endif //NUMREPRESENTATION_WORDSIZESELECTION_H
