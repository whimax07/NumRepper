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
#include "../edit_fields/E_DataUpdateErrors.h"
#include "NumberStructs.h"


class DataModel : public QObject {
Q_OBJECT

private:
    Number data_;

    bool isEmptyNumber_;

    E_FieldTypes updatingField_;

    // TODO(Max): Deprecate this in favour of `updateState_` to allow for more
    //  GUI features.
    bool successfulUpdate_;

    E_DataUpdateErrors updateState_;

    E_WordSizes wordSize_;


public:
    DataModel() : data_ {},
                  isEmptyNumber_(true),
                  updatingField_(E_FieldTypes::NONE),
                  successfulUpdate_{false},
                  wordSize_{E_WordSizes::U32} {  };


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
    /**
     * IMPORTANT: This function can  call `emit generalDataUpdated();`. Be
     * carefully with ordering.
     */
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
    // ===== Data update failure. ==============================================
    void setUpdateState(E_FieldTypes source, E_DataUpdateErrors error) {
        updatingField_ = source;
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
            case E_WordSizes::U8: numBytes = 1; break;
            case E_WordSizes::U16: numBytes = 2; break;
            case E_WordSizes::U32: numBytes = 4; break;
            case E_WordSizes::U64: numBytes = 8; break;
        }
        uint64_t base = -1;
        int bitsToShift = 8 * (8 - numBytes);
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
