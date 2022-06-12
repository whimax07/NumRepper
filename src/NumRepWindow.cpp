#include "NumRepWindow.h"
#include "BinaryEditor.h"
#include "ClickableLabel.h"


void NumRepWindow::buildGui(QWidget *main_panel) {
    this->_mainPanel = main_panel;
    auto edit_panel = new QWidget(_mainPanel);

    _decEdit = EditFields::makeDecEditor(_mainPanel, _dataModel);
    _hexEdit = EditFields::makeHexEditor(_mainPanel, _dataModel);
    _floatEdit = EditFields::makeFloatEditor(_mainPanel, _dataModel);

    auto layout = new QFormLayout(edit_panel);
    layout->addRow("Decimal", _decEdit);
    layout->addRow("Hexadecimal", _hexEdit);
    layout->addRow("Signal Precision", _floatEdit);
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
