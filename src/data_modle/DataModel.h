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
    uint64_t dataField_;

    FieldTypes updatingField_;

    bool successfulUpdate_;


public:
    DataModel() : dataField_{0},
                  updatingField_(FieldTypes::NONE),
                  successfulUpdate_{false} {};

    void setModelData(uint64_t data, FieldTypes source) {
        dataField_ = data;
        updatingField_ = source;
        std::cout << "New dataField_ value is: " << data << std::endl;
    }

    uint64_t getModelData() {
        return dataField_;
    }

    FieldTypes getUpdatingFieldType() {
        return updatingField_;
    }

    void setUpdateSuccessfully(bool success) {
        if (success || successfulUpdate_ != success) {
            successfulUpdate_ = success;
            emit generalDataUpdated();
        } else {
            successfulUpdate_ = success;
        }
    }

    bool isUpdateSuccessful() {
        return successfulUpdate_;
    }


signals:
    void generalDataUpdated();

};


#endif //NUMREPRESENTATION_DATAMODEL_H

#pragma clang diagnostic pop