//
// Created by max on 07/08/22.
//
#include <gtest/gtest.h>
#include "utils/Utils.h"
#include "Tokenizer.h"
#include "token/Symbols.h"
#include "token/NumericToken.h"


using namespace repper;

class CheckTokenOutput {
private:
    const std::vector<std::shared_ptr<Token>> tokens;
    int index = 0;

public:
    explicit CheckTokenOutput(const vector<std::shared_ptr<Token>> &tokens)
            : tokens(tokens) {}

    bool operator()(const auto &expected) {
        if (index >= tokens.size()) return false;
        auto val = tokens[index++];
        return *val == expected;
    }
};



// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}


TEST(Tokenizer, EmptyParse) {
    auto emptyTokens = Tokenizer::tokenize("");
    EXPECT_TRUE(emptyTokens.empty());
}


TEST(Tokenizer, SimpleParse1) {
    auto singleAdd = Tokenizer::tokenize("+");
    EXPECT_TRUE(*singleAdd[0] == symbols::ADD);
    EXPECT_FALSE(*singleAdd[0] == symbols::SUBTRACT);
}


TEST(Tokenizer, SimpleParse2) {
    auto singleAdd = Tokenizer::tokenize("10 + 20");
    EXPECT_TRUE(*singleAdd[0] == NumericToken("10"));
    EXPECT_TRUE(*singleAdd[1] == symbols::ADD);
    EXPECT_TRUE(*singleAdd[2] == NumericToken("20"));

    auto singleAddNoSpaces = Tokenizer::tokenize("10+20");
    EXPECT_TRUE(*singleAddNoSpaces[0] == NumericToken("10"));
    EXPECT_TRUE(*singleAddNoSpaces[1] == symbols::ADD);
    EXPECT_TRUE(*singleAddNoSpaces[2] == NumericToken("20"));
}


TEST(Tokenizer, SimpleParse3) {
    auto singleMultiply = Tokenizer::tokenize("50 * 100");
    auto checker1 = CheckTokenOutput(singleMultiply);
    EXPECT_TRUE(checker1(NumericToken("50")));
    EXPECT_TRUE(checker1(symbols::MULTIPLY));
    EXPECT_TRUE(checker1(NumericToken("100")));

    auto checker3 = CheckTokenOutput(singleMultiply);
    EXPECT_FALSE(checker3(NumericToken("10")));
    EXPECT_FALSE(checker3(NumericToken("10")));
    EXPECT_FALSE(checker3(symbols::ADD));

    auto checker2 = CheckTokenOutput(Tokenizer::tokenize("50*100"));
    EXPECT_TRUE(checker2(NumericToken("50")));
    EXPECT_TRUE(checker2(symbols::MULTIPLY));
    EXPECT_TRUE(checker2(NumericToken("100")));
}


TEST(Tokenizer, AllSymbols) {
    auto tokens1 = Tokenizer::tokenize("(1 << 5.5) / 6 + ((4 >> 1) | 1) - 1");
    auto checker1 = CheckTokenOutput(tokens1);

    EXPECT_TRUE(checker1(symbols::OPEN_BRACKET));
    EXPECT_TRUE(checker1(NumericToken("1")));
    EXPECT_TRUE(checker1(symbols::LEFT_SHIFT));
    EXPECT_TRUE(checker1(NumericToken("5.5")));
    EXPECT_TRUE(checker1(symbols::CLOSE_BRACKET));
    EXPECT_TRUE(checker1(symbols::DIVIDE));
    EXPECT_TRUE(checker1(symbols::NumericToken("6")));
    EXPECT_TRUE(checker1(symbols::ADD));
    EXPECT_TRUE(checker1(symbols::OPEN_BRACKET));
    EXPECT_TRUE(checker1(symbols::OPEN_BRACKET));
    EXPECT_TRUE(checker1(NumericToken("4")));
    EXPECT_TRUE(checker1(symbols::RIGHT_SHIFT));
    EXPECT_TRUE(checker1(NumericToken("1")));
    EXPECT_TRUE(checker1(symbols::CLOSE_BRACKET));
    EXPECT_TRUE(checker1(symbols::BIT_OR));
    EXPECT_TRUE(checker1(NumericToken("1")));
    EXPECT_TRUE(checker1(symbols::CLOSE_BRACKET));
    EXPECT_TRUE(checker1(symbols::SUBTRACT));
    EXPECT_TRUE(checker1(NumericToken("1")));

    auto checker2 = CheckTokenOutput(Tokenizer::tokenize("10 - -20 & 255"));
    EXPECT_TRUE(checker2(NumericToken("10")));
    EXPECT_TRUE(checker2(symbols::SUBTRACT));
    EXPECT_TRUE(checker2(symbols::NEGATE));
    EXPECT_TRUE(checker2(NumericToken("20")));
    EXPECT_TRUE(checker2(symbols::BIT_AND));
    EXPECT_TRUE(checker2(NumericToken("255")));

    auto checker3 = CheckTokenOutput(Tokenizer::tokenize("10 --20"));
    EXPECT_TRUE(checker3(NumericToken("10")));
    EXPECT_TRUE(checker3(symbols::SUBTRACT));
    EXPECT_TRUE(checker3(symbols::NEGATE));
    EXPECT_TRUE(checker3(NumericToken("20")));
}
