//
// Created by max on 23/04/22.
//

#ifndef NUMREPRESENTATION_BINARYEDITOR_H
#define NUMREPRESENTATION_BINARYEDITOR_H

#include <QWidget>

class BinaryEditor : public QWidget {
Q_OBJECT

public slots:
    void valueUpdated(const int bitPosChanged, const bool high);

};


#endif //NUMREPRESENTATION_BINARYEDITOR_H
