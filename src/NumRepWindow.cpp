#include "NumRepWindow.h"
#include "BinaryEditor.h"
#include "ClickableLabel.h"



void NumRepWindow::buildGui(QWidget *main_panel) {
    this->mainPanel = main_panel;
    auto edit_panel = new QWidget(this->mainPanel);

    this->decEdit = new DecEditor(this->mainPanel, _dataModel);

    auto layout = new QFormLayout(edit_panel);
    layout->addRow("Decimal", this->decEdit);
}

//void NumRepWindow::buildGui(QWidget *main_panel) {
//    this->mainPanel = main_panel;
//    auto box_layout = new QVBoxLayout(this->mainPanel);
//    auto edit_panel = new QWidget(this->mainPanel);
//
//
//    this->decEdit = new QLineEdit(this->mainPanel);
//    this->hexEdit = new QLineEdit(this->mainPanel);
//    this->binEdit = new QLineEdit(this->mainPanel);
//    this->floatEdit = new QLineEdit(this->mainPanel);
//
//    auto layout = new QFormLayout(edit_panel);
//    layout->addRow("Decimal", this->decEdit);
//    layout->addRow("Hexadecimal", this->hexEdit);
//    layout->addRow("Binary", this->binEdit);
//    layout->addRow("Floating Point", this->floatEdit);
//
//    auto binaryEditor = new BinaryEditor();
//
//    auto binaryEditPanel = new QWidget(this->mainPanel);
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
