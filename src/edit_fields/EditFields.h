//
// Created by max on 12/06/22.
//

#ifndef NUMREPRESENTATION_EDITFIELDS_H
#define NUMREPRESENTATION_EDITFIELDS_H


#include "GenericEditField.h"


class EditFields {

public:
    static GenericEditField * makeDecEditor(
            QWidget *parent,
            DataModel *dataModel
    );

    static GenericEditField * makeHexEditor(
            QWidget *parent,
            DataModel *dataModel
    );

    static GenericEditField * makeBinEditor(
            QWidget *parent,
            DataModel *dataModel
    );

    static GenericEditField * makeFloatEditor(
            QWidget *parent,
            DataModel *dataModel
    );

    static GenericEditField * makeDoubleEditor(
            QWidget *parent,
            DataModel *dataModel
    );

};


#endif //NUMREPRESENTATION_EDITFIELDS_H
