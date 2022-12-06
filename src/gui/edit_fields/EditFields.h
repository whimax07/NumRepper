//
// Created by max on 12/06/22.
//

#ifndef NUMREPRESENTATION_EDITFIELDS_H
#define NUMREPRESENTATION_EDITFIELDS_H


#include "common/NumberStructs.h"
#include "data_model/DataModel.h"
#include "utils/Utils.h"

#include "GenericEditField.h"
#include "E_DataUpdateErrors.h"


class EditFields {

public:
    static GenericEditField * makeSignedDecEditor(
            QWidget *parent,
            DataModel *dataModel
    );

    static GenericEditField * makeUnsignedDecEditor(
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

};


#endif //NUMREPRESENTATION_EDITFIELDS_H
