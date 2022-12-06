//
// Created by max on 26/07/22.
//

#ifndef REPPARSE_TOKEN_H
#define REPPARSE_TOKEN_H


#include <ostream>
#include <iostream>
#include <memory>



namespace repper {



class Token {

public:
    virtual void emptyFunToken() {  };


public:
    friend bool operator==(const Token &lhs, const Token &rhs) {
        return typeid(lhs) == typeid(rhs) && lhs.isEqual(rhs);
    }

    bool operator!=(const Token &rhs) const {
        return !(rhs == *this);
    };

    friend std::ostream const &operator<<(std::ostream &lhs, const Token &rhs) {
        return lhs << rhs.toString();
    }

    [[nodiscard]] virtual std::string toString() const {
        return "Token{}";
    }


private:
    [[nodiscard]]
    virtual bool isEqual(const Token &rhs) const {
        throw std::logic_error("You can not compare two tokens.");
    }

};


using TokenSPtr = std::shared_ptr<Token>;

}

#endif //REPPARSE_TOKEN_H
