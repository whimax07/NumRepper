//
// Created by max on 16/08/22.
//

#ifndef REPPARSERUNNABLE_NUMBERVARIANT_H
#define REPPARSERUNNABLE_NUMBERVARIANT_H


#include <variant>
#include <cstdint>


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

}


#endif //REPPARSERUNNABLE_NUMBERVARIANT_H
