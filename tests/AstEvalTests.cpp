//
// Created by max on 29/11/22.
//

#include <gtest/gtest.h>

#include "RepParse.h"


using namespace repper;

bool eq(const TypedNumbers& lhs, auto rhs) {
    return std::visit([rhs](auto in) { return in == rhs; }, lhs);
}



TEST(AstEval, basic) {
    auto ast1 = RepParse::parse("5 * 6");
    auto res1 = AST::evaluate(make_shared<AST>(ast1));
    ASSERT_TRUE(eq(res1, 30));

    auto ast2 = RepParse::parse("106168440 & 0xff");
    auto res2 = AST::evaluate(make_shared<AST>(ast2));
    ASSERT_TRUE(eq(res2, 120));
    ASSERT_FALSE(eq(res2, 20));

    ASSERT_TRUE(RepParse::evaluate("(10 * 20) + 30") == RepParse::evaluate("30 + (20 * 10)"));
    ASSERT_TRUE(RepParse::evaluate("(10 * 20) + 30") == RepParse::evaluate("30 + (10 * 20)"));
    ASSERT_TRUE(RepParse::evaluate("(10 * 20) + 30") == RepParse::evaluate("(10 * 20) + 30"));

    EXPECT_THROW(RepParse::evaluate("10.0 & 32"), std::exception);
}

TEST(AstEval, bitOps) {
    auto res1 = RepParse::evaluate("1 << 5");
    ASSERT_TRUE(eq(res1, 32));

    auto res2 = RepParse::evaluate("4751616 >> 3");
    ASSERT_TRUE(eq(res2, 593952));
    ASSERT_FALSE(eq(res2, 593951));
}
