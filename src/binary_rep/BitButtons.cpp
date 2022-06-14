//
// Created by max on 14/06/22.
//

#include "BitButtons.h"


void
BitButtons::makeButtons() {
    auto bin_button_layout = new QGridLayout(this);

    BitButton *buttons[16][4];
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 4; j++) {
            auto bit_button = new BitButton(this, (j * 16) + i);
            bit_button->setText(QString::number(((j * 16) + i)));
            bit_button->setMinimumWidth(1);
            bit_button->setCheckable(true);
            bit_button->setChecked(true);

             connect(
                     bit_button, &BitButton::bitToggled,
                     this, &BitButtons::bitChanged
             );

            buttons[15 - i][3 - j] = bit_button;
            buttons_[(j * 16) + i] = bit_button;
        }
    }

    int count = 0;
    int offset = 0;
    while (count < 16) {
        for (int i = 0; i < 4; i++) {
            bin_button_layout->addWidget(buttons[count][i], i, count + offset);
            bin_button_layout->setColumnMinimumWidth(count + offset, 25);
            bin_button_layout->setColumnStretch(count + offset, 2);
        }

        if (count % 4 == 3) {
            offset ++;
            bin_button_layout->setColumnMinimumWidth(count + offset, 10);
            bin_button_layout->setColumnStretch(count + offset, 1);
        }

        count ++;
    }
}


void
BitButtons::bitChanged(
        bool state,
        int bitNumber
) {
    uint64_t data = dataModel_->getModelData();
    uint64_t one = 1;
    if (state) {
        data = data | one << bitNumber;
    } else {
        data = data & ~(one << bitNumber);
    }

    std::cout << "Bin button " << bitNumber << " changed: "
              << data
              << std::endl;

    dataModel_->setModelData(data, FieldTypes::BIN_EXPAND);
    dataModel_->setUpdateSuccessfully(true);
}


void
BitButtons::dataModelUpdated() {
    if (dataModel_->getUpdatingFieldType() == FieldTypes::BIN_EXPAND) {
        return;
    }

    if (!dataModel_->isUpdateSuccessful()) {
        for (int i = 0; i < 64; i++) {
            buttons_[i]->setChecked(true);
        }
        return;
    }

    uint64_t data = dataModel_->getModelData();
    for (auto & button : buttons_) {
        // When want the buttons to be down when the bit is low.
        button->setChecked((data & 1) == 0);
        data = data >> 1;
    }
}
