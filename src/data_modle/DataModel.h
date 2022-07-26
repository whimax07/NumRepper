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

#include "../edit_fields/E_FieldTypes.h"
#include "../word_size/E_WordSizes.h"



union Number {
    uint8_t u8;
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

    bool isEmptyNumber_;

    E_FieldTypes updatingField_;

    bool successfulUpdate_;

    E_WordSizes wordSize_;


public:
    DataModel() : data_ {},
                  isEmptyNumber_(true),
                  updatingField_(E_FieldTypes::NONE),
                  successfulUpdate_{false},
                  wordSize_{E_WordSizes::I32} {  };


public:
    // =========================================================================
    // ===== Update the core number and attach the source. =====================
    void setData(Number data, E_FieldTypes source) {
        data_ = data;
        updatingField_ = source;
        std::cout << "New dataField_ value is: " << data.u64 << std::endl;
    }

    Number getData() {
        return data_;
    }

    E_FieldTypes getUpdatingFieldType() {
        return updatingField_;
    }


    // =========================================================================
    // ===== Empty number. =====================================================
    void setNumberEmpty(bool isNumberEmpty) {
        isEmptyNumber_ = isNumberEmpty;
    }

    [[nodiscard]]
    bool isNumberEmpty() const {
        return isEmptyNumber_;
    }


    // =========================================================================
    // ===== Data updated successfully. ========================================
    void setUpdateSuccessfully(bool success) {
        if (success || successfulUpdate_ != success) {
            successfulUpdate_ = success;
            emit generalDataUpdated();
        } else {
            successfulUpdate_ = success;
        }
    }

    [[nodiscard]]
    bool isUpdateSuccessful() const {
        return successfulUpdate_;
    }


    // =========================================================================
    // ===== Number word size. =================================================
    void setWordSize(E_WordSizes wordSize) {
        wordSize_ = wordSize;
        updatingField_ = E_FieldTypes::WORD_SIZE;

        // TODO(Max): Check if notting an int of the right size is a better way 
        //  to make the mask. I.e.
        //      uint16_t small_mask = 0;
        //      uint64_t mask = (uint64_t) ~small_mask;
        // or
        //      uint64_t mask = (uint64_t) (~ (uint16_t) 0);
        // data_.u64 = data.u64 & mask;
        int numBytes = 0;
        switch (wordSize) {
            case E_WordSizes::U8: num_bytes = 1; break;
            case E_WordSizes::I16: num_bytes = 2; break;
            case E_WordSizes::I32: num_bytes = 4; break;
            case E_WordSizes::I64: num_bytes = 8; break;
        }
        uint64_t base = -1;
        int bitsToShift = 8 * (8 - num_bytes);
        data_.u64 = data_.u64 & (base >> bitsToShift);

        emit generalDataUpdated();
    }

    E_WordSizes getWordSize() {
        return wordSize_;
    }


signals:
    void generalDataUpdated();

    void dataSizeChanged();

};


#endif //NUMREPRESENTATION_DATAMODEL_H

#pragma clang diagnostic pop
