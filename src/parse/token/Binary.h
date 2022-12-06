//
// Created by max on 26/07/22.
//

#ifndef REPPARSE_BINARY_H
#define REPPARSE_BINARY_H


#include <concepts>
#include <bit>
#include "Operator.h"
#include "Token.h"
#include "NumberVariant.h"
#include "../utils/Utils.h"


namespace repper {

enum class E_Binary {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    RIGHT_SHIFT,
    LEFT_SHIFT,
    BIT_AND,
    BIT_OR
};

constexpr const char *E_BinaryToString(E_Binary e) {
    switch (e) {
        case E_Binary::ADD:
            return "ADD";
        case E_Binary::SUBTRACT:
            return "SUBTRACT";
        case E_Binary::MULTIPLY:
            return "MULTIPLY";
        case E_Binary::DIVIDE:
            return "DIVIDE";
        case E_Binary::RIGHT_SHIFT:
            return "RIGHT_SHIFT";
        case E_Binary::LEFT_SHIFT:
            return "LEFT_SHIFT";
        case E_Binary::BIT_AND:
            return "BITWISE_AND";
        case E_Binary::BIT_OR:
            return "BITWISE_OR";

        default:
            throw std::invalid_argument(
                    "Token type doesn't match an existing enum."
            );
    }
}



class Binary : public Operator {

private:
    const E_Binary id_;

    const int precedence_;

    const bool isLeftAssociative_;


// Constructors and assignment.
public:
    constexpr Binary(E_Binary id, int precedence, bool isLeftAssociative)
    noexcept: id_(id), precedence_(precedence),
              isLeftAssociative_(isLeftAssociative) {}

    Binary(const Binary &toCopy) = default;

    Binary(Binary &&toMove) = default;

    ~Binary() = default;

    Binary & operator=(Binary &&toMove) noexcept;;


// Polymorphism functions.
private:
    void emptyFunToken() override {}

    [[nodiscard]]
    bool isEqual(const Token &rhs) const override {
        auto rhsCasted = dynamic_cast<const Binary *>(&rhs);
        return this->id_ == rhsCasted->id_;
    }


// Getter, Setters and operators.
public:
    std::string toString() const override;

    [[nodiscard]]
    int getPrecedence() const {
        return precedence_;
    }

    [[nodiscard]]
    bool isLeftAssociative() const {
        return isLeftAssociative_;
    }

    TypedNumbers evalTypedNumber(TypedNumbers lhs, TypedNumbers rhs);

    TypedNumbers evalBinary(auto lhs, auto rhs) const;


// Private function to help resolve operands that care if they receive integers
// or floating point numbers. So far they are bitwise And, bitwise Or and bit
// shifts.
private:
    template<std::integral T, std::integral U>
    inline TypedNumbers rightShift(T lhs, U rhs) const;

    template<class T, class U>
    inline TypedNumbers rightShift(T lhs, U rhs) const;

    template<std::integral T, std::integral U>
    inline TypedNumbers leftShift(T lhs, U rhs) const;

    template<class T, class U>
    inline TypedNumbers leftShift(T lhs, U rhs) const;

    template<class T, class U>
    inline TypedNumbers bitAnd(T lhs, U rhs) const;

    template<class T, class U>
    inline TypedNumbers bitOr(T lhs, U rhs) const;

    template<class T, class U>
    [[nodiscard]] inline std::logic_error
    throwCorrectError(const std::string& opName) const;

};



// =============================================================================
// ====== Operators ============================================================
inline Binary &Binary::operator=(Binary &&toMove) noexcept {
    auto temp = Binary(toMove);
    std::swap(*this, temp);
    return *this;
}


inline std::string Binary::toString() const {
    auto sstr = std::ostringstream();
    sstr << "Binary{ Type: " << E_BinaryToString(id_)
         << ", Precedence: " << precedence_
         << ", Left Associative: " << isLeftAssociative_
         << " }";
    return sstr.str();
}


// =============================================================================
// ====== Eval =================================================================
inline TypedNumbers Binary::evalTypedNumber(TypedNumbers lhs, TypedNumbers rhs) {
    return std::visit([&](auto in1, auto in2) { return evalBinary(in1, in2); }, lhs, rhs);
}


TypedNumbers Binary::evalBinary(const auto lhs, const auto rhs) const {
    switch (id_) {
        case E_Binary::MULTIPLY: return lhs * rhs;
        case E_Binary::DIVIDE: return lhs / rhs;
        case E_Binary::ADD: return lhs + rhs;
        case E_Binary::SUBTRACT: return lhs - rhs;
        case E_Binary::RIGHT_SHIFT: return rightShift(lhs, rhs);
        case E_Binary::LEFT_SHIFT: return leftShift(lhs, rhs);
        case E_Binary::BIT_AND: return bitAnd(lhs, rhs);
        case E_Binary::BIT_OR: return bitOr(lhs, rhs);
        default: throw std::logic_error("The operator ID has not been missed.");
    }
}


// =============================================================================
// ====== Right shift ==========================================================
template<class T, class U>
TypedNumbers Binary::rightShift(T lhs, U rhs) const {
    throw std::logic_error(Utils::sstr(
            "The second type of a shift needs to be an integer type, "
            "received: ",
            typeid(U).name()
    ));
}


template<std::integral T, std::integral U>
TypedNumbers Binary::rightShift(T lhs, U rhs) const {
    return lhs >> rhs;
}


// =============================================================================
// ====== Left shift ===========================================================
template<class T, class U>
TypedNumbers Binary::leftShift(T lhs, U rhs) const {
    throw std::logic_error(Utils::sstr(
            "The second type of a shift needs to be an integer type, "
            "received: ",
            typeid(U).name()
    ));
}


template<std::integral T, std::integral U>
TypedNumbers Binary::leftShift(T lhs, U rhs) const {
    return lhs << rhs;
}


// =============================================================================
// ====== Bitwise and ==========================================================
template<class T, class U>
TypedNumbers Binary::bitAnd(T lhs, U rhs) const {
    if constexpr (std::is_floating_point_v<T> || std::is_floating_point_v<U>) {
        throw throwCorrectError<T, U>("Bitwise And");
    } else {
        return lhs & rhs;
    }
}


template<class T, class U>
TypedNumbers Binary::bitOr(T lhs, U rhs) const {
    using StripedT = std::decay_t<T>;
    using StripedU = std::decay_t<U>;

    if constexpr (std::is_floating_point_v<StripedT> || std::is_floating_point_v<StripedU>) {
        throw throwCorrectError<T, U>("Bitwise Or");
    } else {
        return lhs | rhs;
    }
}


// =============================================================================
// ====== Private utils ========================================================
template<class T, class U>
std::logic_error Binary::throwCorrectError(const std::string &opName) const {
    if constexpr (std::is_floating_point_v<T> && std::is_floating_point_v<U>) {
        return std::logic_error(
                opName + " on two floating point values has not defined."
        );
    } else if constexpr (std::is_floating_point_v<T>) {
        return std::logic_error(
                opName + " on a floating point values has not defined. "
                         "LHS is the float."
        );
    } else if constexpr (std::is_floating_point_v<U>) {
        return std::logic_error(
                opName + " on a floating point values has not defined. "
                         "RHS is the float."
        );
    }
}

}

#endif //REPPARSE_BINARY_H
