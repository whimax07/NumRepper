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
#include "../word_size/WordSizes.h"


union Number {
    int16_t i16;
    uint16_t u16;
    int32_t i32;
    uint32_t u32;
    int64_t i64;
    uint64_t u64;
    float f32;
    double f64;

    // This is pretty neat.
    Number() : u64() {}
};


class DataModel : public QObject {
Q_OBJECT

private:
    Number data_;

    FieldTypes updatingField_;

    bool successfulUpdate_;


public:
    DataModel() : data_ {},
                  updatingField_(FieldTypes::NONE),
                  successfulUpdate_{false} {  };

    void setData(Number data, FieldTypes source) {
        data_ = data;
        updatingField_ = source;
        std::cout << "New dataField_ value is: " << data.u64 << std::endl;
    }

    Number getData() {
        return data_;
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

    bool isUpdateSuccessful() const {
        return successfulUpdate_;
    }

    void changeWordSize(WordSizes wordSize) {

    }


signals:
    void generalDataUpdated();

};


#endif //NUMREPRESENTATION_DATAMODEL_H

#pragma clang diagnostic pop