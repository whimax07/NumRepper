//
// Created by max on 06/12/22.
//

#ifndef NUMREPRESENTATION_NUMBERSTRUCTS_H
#define NUMREPRESENTATION_NUMBERSTRUCTS_H

#include <cstdint>
#include <variant>


namespace repper {

using TypedNumbers = std::variant<
        int8_t,
        uint8_t,
        int16_t,
        uint16_t,
        int32_t,
        uint32_t,
        int64_t,
        uint64_t,
        float,
        double
>;

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

    explicit Number(TypedNumbers typedNumber) {
        switch (typedNumber.index()) {
            case 0: i8 = std::get<0>(typedNumber); return;
            case 1: u8 = std::get<1>(typedNumber); return;
            case 2: i16 = std::get<2>(typedNumber); return;
            case 3: u16 = std::get<3>(typedNumber); return;
            case 4: i32 = std::get<4>(typedNumber); return;
            case 5: u32 = std::get<5>(typedNumber); return;
            case 6: i64 = std::get<6>(typedNumber); return;
            case 7: u64 = std::get<7>(typedNumber); return;
            case 8: f32 = std::get<8>(typedNumber); return;
            case 9: f64 = std::get<9>(typedNumber); return;
        }
    }
};

}

#endif //NUMREPRESENTATION_NUMBERSTRUCTS_H
