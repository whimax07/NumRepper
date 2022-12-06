//
// Created by max on 02/08/22.
//

#ifndef REPPARSE_BRACKETS_H
#define REPPARSE_BRACKETS_H


#include "Token.h"



namespace repper {

    enum class E_Brackets {
        OPEN,
        CLOSE
    };

    constexpr const char *E_BracketsToString(E_Brackets e) {
        switch (e) {
            case E_Brackets::OPEN:
                return "OPEN_BRACKET";
            case E_Brackets::CLOSE:
                return "CLOSE_BRACKET";
            default:
                throw std::invalid_argument(
                        "Token type doesn't match an existing enum."
                );
        }
    }


    class Brackets : public Token {

    private:
        const E_Brackets id_;


    public:
        explicit constexpr Brackets(E_Brackets id) noexcept: id_(id) {}

        ~Brackets() = default;


    private:
        void emptyFunToken() override {}

        [[nodiscard]]
        bool isEqual(const Token &rhs) const override {
            auto rhsCasted = dynamic_cast<const Brackets *>(&rhs);
            return this->id_ == rhsCasted->id_;
        }


    public:
        [[nodiscard]] std::string toString() const override {
            auto sstr = std::ostringstream();
            sstr << "Bracket{ Type:" << E_BracketsToString(id_) << " }";
            return sstr.str();
        }

        bool operator==(const Brackets &rhs) const {
            return id_ == rhs.id_;
        }

        bool operator!=(const Brackets &rhs) const {
            return !(rhs == *this);
        }

    };

}



#endif //REPPARSE_BRACKETS_H
