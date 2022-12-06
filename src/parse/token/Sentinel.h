//
// Created by max on 26/07/22.
//

#ifndef REPPARSE_SENTINEL_H
#define REPPARSE_SENTINEL_H


#include "Operator.h"
#include "Token.h"



namespace repper {

    enum class E_Sentinel {
        SENTINEL
    };


    class Sentinel : public Operator {

    private:
        E_Sentinel id_;


    public:
        explicit constexpr Sentinel(E_Sentinel id) noexcept: id_(id) {}

        ~Sentinel() = default;


    private:
        void emptyFunToken() override {}

        [[nodiscard]]
        bool isEqual(const Token &rhs) const override {
            auto rhsCasted = dynamic_cast<const Sentinel *>(&rhs);
            return this->id_ == rhsCasted->id_;
        }


    public:
        [[nodiscard]] std::string toString() const override {
            return "Sentinel{}";
        }

        bool operator==(const Sentinel &rhs) const {
            return id_ == rhs.id_;
        }

        bool operator!=(const Sentinel &rhs) const {
            return !(rhs == *this);
        }

    };

}



#endif //REPPARSE_SENTINEL_H
