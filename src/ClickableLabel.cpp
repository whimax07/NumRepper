//
// Created by max on 23/04/22.
//

#include "ClickableLabel.h"



ClickableLabel::ClickableLabel(
        QWidget* parent, int labelNumber, Qt::WindowFlags f
) : QLabel(parent), labelNumber{labelNumber} { }

ClickableLabel::~ClickableLabel() = default;



void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked(this->labelNumber, true);
}
