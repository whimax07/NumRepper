//
// Created by max on 26/07/22.
//

#ifndef REPPARSE_NUMERICTOKEN_H
#define REPPARSE_NUMERICTOKEN_H


#include <utility>

#include "Token.h"
#include "NumberVariant.h"


namespace repper {


class NumericToken : public Token {

private:
    std::string stringNumber_;


public:
    NumericToken() : stringNumber_() {}

    explicit NumericToken(std::string stringNumber) :
            stringNumber_(std::move(stringNumber)) {}

    NumericToken(const NumericToken &toCopy) = default;

    NumericToken(NumericToken &&toMove) = default;

    ~NumericToken() = default;

    NumericToken & operator=(NumericToken &&toMove) noexcept {
        auto temp = NumericToken(toMove);
        std::swap(*this, temp);
        return *this;
    };


private:
    void emptyFunToken() override {}

    template<size_t NumBytes>
    TypedNumbers parseFloat() {
        if constexpr (NumBytes == 2) {
            throw std::logic_error(
                    "This programme does not support 2 byte floats."
            );
        } else if constexpr (NumBytes == 4) {
            return std::stof(stringNumber_);
        } else {
            return std::stod(stringNumber_);
        }
    }

    template<size_t NumBytes>
    TypedNumbers parseInt() {
        std::string trimmed = stringNumber_;
        int base = 10;
        if (stringNumber_.length() > 2) {
            if (stringNumber_[1] == 'b' || stringNumber_[1] == 'B') {
                base = 2;
                trimmed = trimmed.substr(2);
            } else if (stringNumber_[1] == 'x' || stringNumber_[1] == 'X') {
                base = 16;
                trimmed = trimmed.substr(2);
            }
        }

        if constexpr (NumBytes == 1) {
            return static_cast<uint8_t>(std::stoi(trimmed, nullptr, base));
        } else if constexpr (NumBytes == 2) {
            return static_cast<int16_t>(std::stoi(trimmed, nullptr, base));
        } else if (NumBytes == 4) {
            return std::stoi(trimmed, nullptr, base);
        } else {
            return std::stol(trimmed, nullptr, base);
        }
    }


public:
    [[nodiscard]] std::string toString() const override {
        auto sstr = std::ostringstream();
        sstr << "NumericToken{ String:" << stringNumber_ << " }";
        return sstr.str();
    }

    [[nodiscard]]
    const std::string &getStringNumber() const {
        return stringNumber_;
    }

    void setStringNumber(const std::string &stringNumber) {
        stringNumber_ = stringNumber;
    }

    TypedNumbers parse() {
        if (stringNumber_.find('.') != std::string::npos) {
            return parseFloat<8>();
        } else {
            return parseInt<8>();
        }
    }

private:
    [[nodiscard]] bool isEqual(const Token &rhs) const override {
        if (auto rhsNumToken = dynamic_cast<const NumericToken *>(&rhs)) {
            return stringNumber_ == rhsNumToken->stringNumber_;
        }

        return false;
    }

};

}


#endif //REPPARSE_NUMERICTOKEN_H
