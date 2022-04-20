#include "NumRepWindow.h"


void NumRepWindow::build_gui(QWidget *window) {
    this->_window = window;

    this->_test_label = new QLabel(this->_window);
    this->_test_label->setText("Some Test Text.\nGo ME!");

    this->_test_edit = new QLineEdit(this->_window);

    auto layout = new QFormLayout(this->_window);
    layout->addRow(this->_test_label, this->_test_edit);
}
