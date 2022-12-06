//
// Created by max on 02/08/22.
//

#ifndef REPPARSE_COMPARE_H
#define REPPARSE_COMPARE_H


#include <stdexcept>
#include <memory>
#include "Binary.h"
#include "Unary.h"
#include "Sentinel.h"


namespace repper {

    class Compare {

    public:
        static bool precedence(
                const TokenSPtr& operator1, const TokenSPtr& operator2
        ) {
            auto b1 = dynamic_pointer_cast<Binary>(operator1);
            auto b2 = dynamic_pointer_cast<Binary>(operator2);
            if (b1 != nullptr && b2 != nullptr) {
                return (b1->getPrecedence() < b2->getPrecedence())
                       || (b1->isLeftAssociative()
                           && b1->getPrecedence() == b2->getPrecedence());
            }

            auto u1 = dynamic_pointer_cast<Unary>(operator1);
            if (u1 != nullptr && b2 != nullptr) {
                return u1->getPrecedence() <= b2->getPrecedence();
            }

            auto u2 = dynamic_pointer_cast<Unary>(operator2);
            if (u2 != nullptr) {
                return false;
            }

            auto s1 = dynamic_pointer_cast<Sentinel>(operator1);
            if (s1 != nullptr) {
                return false;
            }

            auto s2 = dynamic_pointer_cast<Sentinel>(operator2);
            if (s2 != nullptr) {
                return true;
            }


            throw std::logic_error("Unexpected operator types.");
        }
    };

}


#endif //REPPARSE_COMPARE_H
