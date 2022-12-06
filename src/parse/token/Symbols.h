//
// Created by max on 02/08/22.
//

#ifndef REPPARSE_SYMBOLS_H
#define REPPARSE_SYMBOLS_H


#include "Binary.h"
#include "Unary.h"
#include "Sentinel.h"
#include "Brackets.h"
#include "End.h"


namespace symbols {

    using namespace repper;


    static constexpr End END = End(E_End::END);

    static constexpr Sentinel SENTINEL = Sentinel(E_Sentinel::SENTINEL);

    static constexpr Brackets OPEN_BRACKET = Brackets(E_Brackets::OPEN);
    static constexpr Brackets CLOSE_BRACKET = Brackets(E_Brackets::CLOSE);

    static constexpr Unary NEGATE = Unary(E_Unary::NEGATE, 2);

    static constexpr Binary ADD = Binary(E_Binary::ADD, 4, true);
    static constexpr Binary SUBTRACT = Binary(E_Binary::SUBTRACT, 4, true);
    static constexpr Binary MULTIPLY = Binary(E_Binary::MULTIPLY, 3, true);
    static constexpr Binary DIVIDE = Binary(E_Binary::DIVIDE, 3, true);

    static constexpr Binary RIGHT_SHIFT = Binary(E_Binary::RIGHT_SHIFT, 5, true);
    static constexpr Binary LEFT_SHIFT = Binary(E_Binary::LEFT_SHIFT, 5, true);
    static constexpr Binary BIT_AND = Binary(E_Binary::BIT_AND, 8, true);
    static constexpr Binary BIT_OR = Binary(E_Binary::BIT_OR, 10, true);

}


#endif //REPPARSE_SYMBOLS_H
