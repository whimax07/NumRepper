#include <QPushButton>

#include "NumRepWindow.h"
#include "BinaryEditor.h"
#include "ClickableLabel.h"


void NumRepWindow::buildGui(QWidget *main_panel) {
    this->_mainPanel = main_panel;
    auto main_panel_layout = new QVBoxLayout(main_panel);


    auto edit_panel = new QWidget(_mainPanel);
    main_panel_layout->addWidget(edit_panel);

    _decEdit = EditFields::makeDecEditor(edit_panel, _dataModel);
    _hexEdit = EditFields::makeHexEditor(edit_panel, _dataModel);
    _floatEdit = EditFields::makeFloatEditor(edit_panel, _dataModel);
    _doubleEdit = EditFields::makeDoubleEditor(edit_panel, _dataModel);

    auto layout = new QFormLayout(edit_panel);
    layout->addRow("Decimal", _decEdit);
    layout->addRow("Hexadecimal", _hexEdit);
    layout->addRow("Signal Precision", _floatEdit);
    layout->addRow("Double Precision", _doubleEdit);
    main_panel_layout->addLayout(layout);


    auto binary_edit = new QWidget(_mainPanel);
    main_panel_layout->addWidget(binary_edit);

    auto bin_button_layout = new QGridLayout(binary_edit);
    main_panel_layout->addLayout(bin_button_layout);


    QPushButton *buttons[16][4];
    for (int i = 15; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            auto clickableButton = new QPushButton(binary_edit);
            clickableButton->setText(QString::number(((j * 16) + i)));
             clickableButton->setMinimumWidth(1);
            buttons[15 - i][3 - j] = clickableButton;
        }
    }


    // connect(
    //         clickableButton, &ClickableLabel::clicked,
    //         binaryEditor, &BinaryEditor::valueUpdated
    // );




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


//void NumRepWindow::buildGui(QWidget *main_panel) {
//    this->_mainPanel = main_panel;
//    auto box_layout = new QVBoxLayout(this->_mainPanel);
//    auto edit_panel = new QWidget(this->_mainPanel);
//
//
//    this->_decEdit = new QLineEdit(this->_mainPanel);
//    this->_hexEdit = new QLineEdit(this->_mainPanel);
//    this->binEdit = new QLineEdit(this->_mainPanel);
//    this->_floatEdit = new QLineEdit(this->_mainPanel);
//
//    auto layout = new QFormLayout(edit_panel);
//    layout->addRow("Decimal", this->_decEdit);
//    layout->addRow("Hexadecimal", this->_hexEdit);
//    layout->addRow("Binary", this->binEdit);
//    layout->addRow("Floating Point", this->_floatEdit);
//
//    auto binaryEditor = new BinaryEditor();
//
//    auto binaryEditPanel = new QWidget(this->_mainPanel);
//    auto binButtonLayout = new QHBoxLayout(binaryEditPanel);
//    for (int i = 0; i < 10; i++) {
//        auto clickableButton = new ClickableLabel(binaryEditPanel, i);
//        clickableButton->setText(QString::fromStdString(std::to_string(i)));
//        connect(
//                clickableButton, &ClickableLabel::clicked,
//                binaryEditor, &BinaryEditor::valueUpdated
//        );
//        binButtonLayout->addWidget(clickableButton);
//    }
//
//    box_layout->addWidget(edit_panel);
//    box_layout->addWidget(binaryEditPanel);
//}
