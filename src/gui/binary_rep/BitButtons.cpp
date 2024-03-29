//
// Created by max on 14/06/22.
//

#include "BitButtons.h"


// We want the buttons to be down when the bit is low.
#define setBits(button, number) \
    (button)->setChecked(((number) & 1) == 1); \
    (number) = (number) >> 1;



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
            bit_button->setChecked(false);

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
    auto data = dataModel_->getData();
    uint64_t one = 1;
    if (state) {
        data.u64 = data.u64 | one << bitNumber;
    } else {
        data.u64 = data.u64 & ~(one << bitNumber);
    }

    std::cout << "Bin button " << bitNumber << " changed: " << data.u64
              << std::endl;

    dataModel_->setNumberEmpty(data.u64 == 0);
    dataModel_->setData(data, E_FieldTypes::BIN_EXPAND);
    dataModel_->setUpdateSuccessfully(true);
}


void
BitButtons::dataModelUpdated() {
    if (dataModel_->getUpdatingFieldType() == E_FieldTypes::BIN_EXPAND) {
        return;
    }

    if (!dataModel_->isUpdateSuccessful()) {
        for (auto & button : buttons_) {
            button->setChecked(true);
        }
        return;
    }

    auto data = dataModel_->getData();
    for (auto & button : buttons_) {
        switch (dataModel_->getWordSize()) {
            case E_WordSizes::U8: setBits(button, data.u8); break;
            case E_WordSizes::U16: setBits(button, data.u16); break;
            case E_WordSizes::U32: setBits(button, data.u32); break;
            case E_WordSizes::U64: setBits(button, data.u64); break;
        }
    }
}
