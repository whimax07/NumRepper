//
// Created by max on 11/07/22.
//

#ifndef REPPARSE_TOKENIZER_H
#define REPPARSE_TOKENIZER_H


#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <regex>
#include "token/Token.h"


namespace repper {

using namespace std;


class Tokenizer {

public:
    using Regex = std::__cxx11::basic_regex<char> &;


private:
    std::string input_;

    std::vector<TokenSPtr> tokens_;

    uint64_t fast_ = 0;

    uint64_t slow_ = 0;


public:
    ~Tokenizer() = default;

    static std::vector<TokenSPtr> tokenize(std::string toTokenize) {
        auto tokenizer = Tokenizer(std::move(toTokenize));
        return tokenizer.tokens_;
    }


private:
    explicit Tokenizer(std::string input)
            : input_(std::move(input)), tokens_() {
        start();
    }

    void start();

    bool checkIfOperator();

    bool checkIfBracket();

    bool checkIfNumber();

    void parseHex();

    void parseBin();

    void parseDec();

    void addNumberToken(Regex pattern);

    bool isSubtract();

    TokenSPtr getLastToken();

};

}


#endif //REPPARSE_TOKENIZER_H
