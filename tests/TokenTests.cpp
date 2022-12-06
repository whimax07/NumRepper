//
// Created by max on 29/11/22.
//
#include <gtest/gtest.h>
#include "token/NumericToken.h"
#include "token/Symbols.h"


using namespace repper;

TEST(NumericToke, equals) {
    bool test = NumericToken("10") == NumericToken("10");
    EXPECT_TRUE(test);
    EXPECT_FALSE(NumericToken("10") == NumericToken("20"));
}


TEST(Brackets, equals) {
    bool test = symbols::OPEN_BRACKET == symbols::OPEN_BRACKET;
    EXPECT_TRUE(test);
    EXPECT_FALSE(symbols::OPEN_BRACKET == symbols::CLOSE_BRACKET);
}


TEST(End, equals) {
    EXPECT_TRUE(symbols::END == symbols::END);
}


TEST(Operator, equals) {
    EXPECT_TRUE(symbols::SENTINEL == symbols::SENTINEL);
    EXPECT_TRUE(symbols::NEGATE == symbols::NEGATE);
    EXPECT_TRUE(symbols::ADD == symbols::ADD);

    EXPECT_FALSE(symbols::SENTINEL == symbols::NEGATE);
    EXPECT_FALSE(symbols::SENTINEL == symbols::MULTIPLY);

    EXPECT_FALSE(symbols::NEGATE == symbols::SUBTRACT);
}
