#include <QPushButton>

#include "NumRepWindow.h"
#include "word_size/WordSizeSelection.h"



void
NumRepWindow::buildGui(
        QWidget *main_panel
) {
    this->_mainPanel = main_panel;
    auto main_panel_layout = new QVBoxLayout(main_panel);

    auto num_bytes_window = new WordSizeSelection(_dataModel);
    main_panel_layout->addWidget(num_bytes_window);

    auto edit_panel = new QWidget(_mainPanel);
    main_panel_layout->addWidget(edit_panel);

    _decEdit = EditFields::makeDecEditor(edit_panel, _dataModel);
    _hexEdit = EditFields::makeHexEditor(edit_panel, _dataModel);
    _binEdit = EditFields::makeBinEditor(edit_panel, _dataModel);
    _floatEdit = EditFields::makeFloatEditor(edit_panel, _dataModel);

    auto layout = new QFormLayout(edit_panel);
    layout->addRow("Decimal", _decEdit);
    layout->addRow("Hexadecimal", _hexEdit);
    layout->addRow("Binary", _binEdit);
    layout->addRow("Floating Point", _floatEdit);


    _bitButtons = new BitButtons(main_panel, _dataModel);
    main_panel_layout->addWidget(_bitButtons);
}
