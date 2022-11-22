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

    _sDecEdit = EditFields::makeSignedDecEditor(edit_panel, _dataModel);
    _uDecEdit = EditFields::makeUnsignedDecEditor(edit_panel, _dataModel);
    _hexEdit = EditFields::makeHexEditor(edit_panel, _dataModel);
    _binEdit = EditFields::makeBinEditor(edit_panel, _dataModel);
    _floatEdit = EditFields::makeFloatEditor(edit_panel, _dataModel);

    auto textEditLayout = new QFormLayout(edit_panel);
    textEditLayout->addRow("Decimal, Signed", _sDecEdit);
    textEditLayout->addRow("Decimal, Unsigned", _uDecEdit);
    textEditLayout->addRow("Hexadecimal", _hexEdit);
    textEditLayout->addRow("Binary", _binEdit);
    textEditLayout->addRow("Floating Point", _floatEdit);


    _bitButtons = new BitButtons(main_panel, _dataModel);
    main_panel_layout->addWidget(_bitButtons);
}
