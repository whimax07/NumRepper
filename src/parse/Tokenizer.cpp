//
// Created by max on 11/07/22.
//

#include <regex>
#include "Tokenizer.h"
#include "token/Symbols.h"
#include "token/NumericToken.h"


namespace repper {

    void
    Tokenizer::start() {
        while (fast_ < input_.length()) {
            if (std::isspace(input_[fast_])) {
                fast_++;
                continue;
            }

            if (checkIfOperator()) {
                fast_++;
                continue;
            }

            if (checkIfBracket()) {
                fast_++;
                continue;
            }

            if (checkIfNumber()) {
                fast_++;
                continue;
            }

            throw std::exception();
        }
    }


    bool
    Tokenizer::isSubtract() {
        if (tokens_.empty()) {
            return false;
        }

        auto lastToken = getLastToken();

        auto number
                = dynamic_pointer_cast<NumericToken>(lastToken);
        bool isNumber = number != nullptr;

        bool isCloseBracket = false;
        if (auto bracket
                = dynamic_pointer_cast<Brackets>(lastToken)) {
            isCloseBracket = *bracket == symbols::CLOSE_BRACKET;
        }

        return isNumber || isCloseBracket;
    }


    bool
    Tokenizer::checkIfOperator() {
        // NOTE(Max): Can this be replaced with regex and a hashmap? The NEGATE
        // and SUBTRACT operator sharing a symbol pattern makes it more than
        // trivial harder.
        switch (input_[fast_]) {
            // Arithmetic operators.
            case '*':
                tokens_.push_back(make_shared<Binary>(symbols::MULTIPLY));
                break;
            case '/':
                tokens_.push_back(make_shared<Binary>(symbols::DIVIDE));
                break;
            case '+':
                tokens_.push_back(make_shared<Binary>(symbols::ADD));
                break;
            case '-': {
                if (isSubtract()) {
                    tokens_.push_back(make_shared<Binary>(symbols::SUBTRACT));
                } else {
                    tokens_.push_back(make_shared<Unary>(symbols::NEGATE));
                }
                break;

            // Bit operators.
            case '&':
                tokens_.push_back(make_shared<Binary>(symbols::BIT_AND));
                break;
            case '|':
                tokens_.push_back(make_shared<Binary>(symbols::BIT_OR));
                break;
            case '>':
                if (input_.length() >= fast_ + 1 && input_[fast_ + 1] == '>') {
                    tokens_.push_back(
                            make_shared<Binary>(symbols::RIGHT_SHIFT)
                    );
                    // Two char token so add an extra increment.
                    fast_ ++;
                }
                break;
            case '<':
                if (input_.length() >= fast_ + 1 && input_[fast_ + 1] == '<') {
                    tokens_.push_back(make_shared<Binary>(symbols::LEFT_SHIFT));
                    // Two char token so add an extra increment.
                    fast_ ++;
                }
                break;
            }

            default:
                return false;
        }

        return true;
    }


    bool
    Tokenizer::checkIfBracket() {
        bool out = true;

        switch (input_[fast_]) {
            case '(':
                tokens_.push_back(make_shared<Brackets>(symbols::OPEN_BRACKET));
                break;
            case ')':
                tokens_.push_back(make_shared<Brackets>(symbols::CLOSE_BRACKET));
                break;
            default:
                out = false;
        }

        return out;
    }


    bool
    Tokenizer::checkIfNumber() {
        std::regex numbers("[0-9]");
        if (!std::regex_search(input_.substr(fast_, 1), numbers)) {
            return false;
        }

        slow_ = fast_;

        if (fast_ + 1 < input_.length()) {
            switch (input_[fast_ + 1]) {
                case 'x':
                case 'X':
                    if (fast_ + 2 > input_.length()) {
                        throw std::logic_error(
                                "Hex indicator \"0x\" without a value."
                        );
                    }
                    parseHex();
                    break;
                case 'b':
                case 'B':
                    if (fast_ + 2 > input_.length()) {
                        throw std::logic_error(
                                "Bin indicator \"0b\" without a value."
                        );
                    }
                    parseBin();
                    break;
                default:
                    parseDec();
            }
        } else {
            parseDec();
        }

        return true;
    }


    void
    Tokenizer::parseHex() {
        std::regex hexDigits("0[xX][0-9aAbBcCdDeEfF_,]+");
        addNumberToken(hexDigits);
    }


    void
    Tokenizer::parseBin() {
        std::regex binDigits("0[bB][0-1_,]+");
        addNumberToken(binDigits);
    }


    void
    Tokenizer::parseDec() {
        std::regex decDigits("[0-9_,]+[\\.]?[0-9_,]*");
        addNumberToken(decDigits);
    }


    void
    Tokenizer::addNumberToken(
            Regex pattern
    ) {
        std::smatch results;
        std::string str = input_.substr(fast_);
        bool found = std::regex_search(str, results, pattern);

        if (!found) {
            throw std::exception();
        }

        auto length = results[0].str().length();
        tokens_.push_back(make_shared<NumericToken>(
                NumericToken(input_.substr(slow_, length))
        ));
        fast_ += length - 1;
    }


    TokenSPtr
    Tokenizer::getLastToken() {
        assert(!tokens_.empty());
        return tokens_[tokens_.size() - 1];
    }

}
