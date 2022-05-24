//
// Created by max on 24/05/22.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#ifndef NUMREPRESENTATION_DATAMODEL_H
#define NUMREPRESENTATION_DATAMODEL_H


#include <cstdint>
#include <iostream>

#include <QtCore>

#include "../edit_fields/FieldTypes.h"


class DataModel : public QObject {
Q_OBJECT

private:
    uint64_t _dataField;


public:
    DataModel() : _dataField{0} {};

    void setModelData(uint64_t data, FieldTypes source) {
        _dataField = data;
        std::cout << "New _dataField value is: " << data <<std::endl;
        emit dataUpdated(data, source);
    }


signals:
    void dataUpdated(uint64_t data, FieldTypes source);

};


#endif //NUMREPRESENTATION_DATAMODEL_H

#pragma clang diagnostic pop