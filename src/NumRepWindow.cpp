#include <QPushButton>

#include "NumRepWindow.h"
#include "BinaryEditor.h"
#include "ClickableLabel.h"


QWidget *
createBinEdit(
        QWidget *main_panel
);


void NumRepWindow::buildGui(QWidget *main_panel) {
    this->_mainPanel = main_panel;
    auto main_panel_layout = new QVBoxLayout(main_panel);


    auto edit_panel = new QWidget(_mainPanel);
    main_panel_layout->addWidget(edit_panel);

    _decEdit = EditFields::makeDecEditor(edit_panel, _dataModel);
    _hexEdit = EditFields::makeHexEditor(edit_panel, _dataModel);
    _binEdit = EditFields::makeBinEditor(edit_panel, _dataModel);
    _floatEdit = EditFields::makeFloatEditor(edit_panel, _dataModel);
//    _doubleEdit = EditFields::makeDoubleEditor(edit_panel, _dataModel);

    auto layout = new QFormLayout(edit_panel);
    layout->addRow("Decimal", _decEdit);
    layout->addRow("Hexadecimal", _hexEdit);
    layout->addRow("Binary", _binEdit);
    layout->addRow("Signal Precision", _floatEdit);
//    layout->addRow("Double Precision", _doubleEdit);
    main_panel_layout->addLayout(layout);


    main_panel_layout->addWidget(createBinEdit(main_panel));
}


QWidget *
createBinEdit(
        QWidget *main_panel
) {
    auto binary_edit = new QWidget(main_panel);
    auto bin_button_layout = new QGridLayout(binary_edit);


    QPushButton *buttons[16][4];
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 4; j++) {
            auto clickableButton = new QPushButton(binary_edit);
            clickableButton->setText(QString::number(((j * 16) + i)));
            clickableButton->setMinimumWidth(1);
            clickableButton->setCheckable(true);

            // connect(
            //         clickableButton, &ClickableLabel::clicked,
            //         binaryEditor, &BinaryEditor::valueUpdated
            // );

            buttons[15 - i][3 - j] = clickableButton;
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

    return binary_edit;
}
