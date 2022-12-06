//
// Created by max on 26/07/22.
//

#ifndef REPPARSE_END_H
#define REPPARSE_END_H


#include "Token.h"



namespace repper {

    enum class E_End {
        END
    };


    class End : public Token {

    private:
        const E_End id_;


    public:
        explicit constexpr End(E_End id) noexcept: id_(id) {}

        ~End() = default;


    private:
        void emptyFunToken() override {}

        [[nodiscard]]
        bool isEqual(const Token &rhs) const override {
            auto rhsCasted = dynamic_cast<const End *>(&rhs);
            return this->id_ == rhsCasted->id_;
        }


    public:
        bool operator==(const End &rhs) const {
            return id_ == rhs.id_;
        }

        bool operator!=(const End &rhs) const {
            return !(rhs == *this);
        }

        [[nodiscard]] std::string toString() const override {
            return "End{}";
        }

    };

}


#endif //REPPARSE_END_H
