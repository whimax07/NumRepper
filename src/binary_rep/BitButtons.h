//
// Created by max on 14/06/22.
//

#ifndef NUMREPRESENTATION_BITBUTTONS_H
#define NUMREPRESENTATION_BITBUTTONS_H


#include <QPushButton>
#include <QGridLayout>

#include "../data_model/DataModel.h"



class BitButton : public QPushButton {
Q_OBJECT

private:
    int bitNumber_;


public:
    BitButton(QWidget *parent, int bitNumber) :
            QPushButton(parent),
            bitNumber_(bitNumber)
    {
        connect(
                this, &BitButton::clicked,
                this, &BitButton::passOnBitChange
        );
    }


private:
    void passOnBitChange(bool state) {
        emit this->bitToggled(state, this->bitNumber_);
    }


signals:
    void bitToggled(bool state, int bitNumber);

};



class BitButtons : public QWidget {
Q_OBJECT

private:
    DataModel *dataModel_;

    BitButton *buttons_[64];


public:
    BitButtons(QWidget *main_panel, DataModel *dataModel) :
            QWidget(main_panel), dataModel_(dataModel), buttons_() {

        makeButtons();

        connect(
                dataModel_, &DataModel::generalDataUpdated,
                this, &BitButtons::dataModelUpdated
        );
    }


private:
    void makeButtons();


private slots:
    void bitChanged(bool state, int bitNumber);

    void dataModelUpdated();

};


#endif //NUMREPRESENTATION_BITBUTTONS_H
