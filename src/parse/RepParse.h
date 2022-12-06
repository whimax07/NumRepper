//
// Created by max on 09/07/22.
//

#ifndef REPPARSE_REPPARSE_H
#define REPPARSE_REPPARSE_H


#include <string>
#include "Tokenizer.h"
#include "tree/AST.h"
#include "token/Sentinel.h"
#include "token/Symbols.h"


namespace repper {

    /**
     * An implementation from <a href="https://www.engr.mun.ca/~theo/Misc/exp_parsing.htm">
     * Parsing Expressions by Recursive Descent Theodore Norvell (C) 1999 with
     * updates later on.</a>
     */
    class RepParse {

    private:
        vector<TokenSPtr> tokens_ {};

        string toParse_ = {};

        stack<OperatorSPtr> operators_ {};

        stack<AST> operands_ {};

        size_t currentPosition_ = 0;


    public:
        RepParse() = default;

        explicit RepParse(string toParse) : toParse_(std::move(toParse)) {}

        ~RepParse() = default;


    public:
        static AST parse(const string &stringToParse);

        static TypedNumbers evaluate(const string &toEval);


    private:
        AST parse();

        void parseE();

        void parseP();

        void pushOperator(const OperatorSPtr& _operator);

        void popOperator();

        void expect(const Token &token);

        shared_ptr<Token> next();

        void consume();

    };

}

#endif //REPPARSE_REPPARSE_H
