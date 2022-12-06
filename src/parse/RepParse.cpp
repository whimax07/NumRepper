//
// Created by max on 09/07/22.
//

#include "RepParse.h"

#include "utils/Utils.h"
#include "token/Compare.h"
#include "token/NumericToken.h"



namespace repper {

    // =========================================================================
    // ===== Public methods. ===================================================
    AST
    RepParse::parse(
            const string &stringToParse
    ) {
        auto parser = RepParse(stringToParse);
        return parser.parse();
    }

    TypedNumbers
    RepParse::evaluate(
            const string &toEval
    ) {
        return AST::evaluate(make_shared<AST>(RepParse::parse(toEval)));
    }


    // =========================================================================
    // ===== Private methods. ==================================================
    AST
    RepParse::parse() {
        if (toParse_.empty()) {
            // Return an empty AST.
            return {};
        }

        tokens_ = Tokenizer::tokenize(toParse_);

        operators_.push(make_shared<Sentinel>(symbols::SENTINEL));
        parseE();
        expect(symbols::END);
        return operands_.top();
    }


    /**
     * This is a recursive function but I like the way the alg flows with the
     * recursion. Also I don't know how to change it to a while loop of the top
     * of my head.
     */
    void
    RepParse::parseE() {
        parseP();

        while (auto binary = dynamic_pointer_cast<Binary>(next())) {
            pushOperator(binary);
            consume();
            parseP();
            binary = dynamic_pointer_cast<Binary>(next());
        }

        while (*operators_.top() != symbols::SENTINEL) {
            popOperator();
        }
    }


    /**
     * This is a recursive function but I like the way the alg flows with the
     * recursion. Also I don't know how to change it to a while loop of the top
     * of my head.
     */
    void
    RepParse::parseP() {
        auto nextT = next();

        if (auto numericToken = dynamic_pointer_cast<NumericToken>(nextT)) {
            operands_.push(AST(numericToken->parse()));
            consume();
            return;
        }

        if (auto bracket = dynamic_pointer_cast<Brackets>(nextT);
                bracket != nullptr && *bracket == symbols::OPEN_BRACKET) {
            consume();
            operators_.push(make_shared<Sentinel>(symbols::SENTINEL));
            parseE();
            expect(symbols::CLOSE_BRACKET);
            operators_.pop();
            return;
        }

        if (auto unary = dynamic_pointer_cast<Unary>(nextT)) {
            pushOperator(unary);
            consume();
            parseP();
            return;
        }

        throw logic_error(Utils::sstr(
                "Unexpected type. The next token was expected to be numeric, an "
                "open bracket or a unary operator when the parse reached this "
                "token. Token: ", nextT
        ));
    }


    void
    RepParse::pushOperator(
            const OperatorSPtr& _operator
    ) {
        while (Compare::precedence(operators_.top(), _operator)) {
            popOperator();
        }

        operators_.push(_operator);
    }


    void
    RepParse::popOperator() {
        auto anOperator = operators_.top();
        operators_.pop();

        if (auto binary = dynamic_pointer_cast<Binary>(anOperator)) {
            AST operand_2 = operands_.top();
            operands_.pop();
            AST operand_1 = operands_.top();
            operands_.pop();

            operands_.push(AST(
                    *binary,
                    make_shared<AST>(operand_1),
                    make_shared<AST>(operand_2)
            ));

            return;
        }

        if (auto unary = dynamic_pointer_cast<Unary>(anOperator)) {
            AST operand = operands_.top();
            operands_.pop();

            operands_.push(AST(
                    *unary,
                    make_shared<AST>(operand)
            ));

            return;
        }

        throw std::logic_error(Utils::sstr(
                "Received a operator that wasn't Binary or Unary. Operator: ",
                anOperator
        ));
    }


    void
    RepParse::expect(
            const Token &token
    ) {
        if (*next() == token) {
            consume();
        } else {
            throw std::logic_error(Utils::sstr(
                    "Expected token: ", token.toString(), ". Received: ", next()->toString()
            ));
        }
    }


    shared_ptr<Token>
    RepParse::next() {
        if (currentPosition_ < tokens_.size()) {
            return tokens_[currentPosition_];
        } else {
            return make_shared<End>(symbols::END);
        }
    }


    void
    RepParse::consume() {
        currentPosition_++;
    }

}
