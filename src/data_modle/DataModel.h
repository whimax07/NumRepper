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
#include "../word_size/E_WordSizes.h"


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

    E_WordSizes wordSize_;


public:
    DataModel() : data_ {},
                  updatingField_(FieldTypes::NONE),
                  successfulUpdate_{false},
                  wordSize_{E_WordSizes::U32} {  };

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

    void setWordSize(E_WordSizes wordSize) {
        wordSize_ = wordSize;

        emit dataSizeChanged();
    }

    E_WordSizes getWordSize() {
        return wordSize_;
    }

    void notifyEmptyField() {
        emit processEmptyField();
    }


signals:
    void generalDataUpdated();

    void dataSizeChanged();

    void processEmptyField();

};


#endif //NUMREPRESENTATION_DATAMODEL_H

#pragma clang diagnostic pop