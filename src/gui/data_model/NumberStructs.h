//
// Created by max on 06/12/22.
//

#ifndef NUMREPRESENTATION_NUMBERSTRUCTS_H
#define NUMREPRESENTATION_NUMBERSTRUCTS_H

#include "../edit_fields/E_DataUpdateErrors.h"
#include "../word_size/E_WordSizes.h"
#include "../edit_fields/E_FieldTypes.h"
#include <QtCore>
#include <iostream>
#include <cstdint>

union Number {
    int8_t i8;
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

#endif //NUMREPRESENTATION_NUMBERSTRUCTS_H
