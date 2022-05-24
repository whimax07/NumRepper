//
// Created by max on 23/04/22.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#ifndef NUMREPRESENTATION_CLICKABLELABEL_H
#define NUMREPRESENTATION_CLICKABLELABEL_H

#include <QWidget>
#include <QLabel>


class ClickableLabel : public QLabel {
Q_OBJECT

private:
    int labelNumber;


public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, int labelNumber = -1,
                            Qt::WindowFlags f = Qt::WindowFlags());

    ~ClickableLabel() override;


signals:
    void clicked(int buttonNumber, bool high);


protected:
    void mousePressEvent(QMouseEvent* event) override;

};


#endif //NUMREPRESENTATION_CLICKABLELABEL_H

#pragma clang diagnostic pop
