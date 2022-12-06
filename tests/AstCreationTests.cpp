//
// Created by max on 16/08/22.
//

#include <gtest/gtest.h>

#include <utility>
#include "token/Symbols.h"
#include "tree/AST.h"
#include "RepParse.h"


using namespace repper;


shared_ptr<AST> mnum(int64_t in) {
    return make_shared<AST>(AST(TypedNumbers(in)));
}

shared_ptr<AST> mflo(double in) {
    return make_shared<AST>(AST(TypedNumbers(in)));
}

shared_ptr<AST> mast(AST in) {
    return make_shared<AST>(in);
}

shared_ptr<AST> mast(NodeTypes op, shared_ptr<AST> left) {
    return mast(AST(std::move(op), std::move(left)));
}

shared_ptr<AST> mast(NodeTypes op, shared_ptr<AST> left, shared_ptr<AST> right) {
    return mast(AST(std::move(op), std::move(left), std::move(right)));
}



TEST(AstParsing, basic) {
    auto myAst = AST(
            TypedNumbers {(int32_t) 10}
    );

    visit(
            [](auto toPrint) { std::cout << toPrint << std::endl; },
            AST::evaluate(std::make_shared<AST>(myAst))
    );


    auto floatAST = AST(
            TypedNumbers {(float) 10}
    );

    visit(
            [](auto toPrint) { std::cout << toPrint << std::endl; },
            AST::evaluate(std::make_shared<AST>(floatAST))
    );
}


TEST(AstParsing, basic_expresions) {
    auto ast = AST(symbols::ADD, mnum(10), mnum(20));
    auto genAst = RepParse::parse("10 + 20");
    ASSERT_TRUE(genAst == ast);

    auto ast5 = AST(symbols::ADD, mnum(20), mnum(20));
    auto gen5 = RepParse::parse("10 + 20");
    ASSERT_FALSE(ast5 == gen5);

    auto ast2 = AST(symbols::ADD, make_shared<AST>(ast), mnum(30));
    auto gen2 = RepParse::parse("10 + 20 + 30");
    ASSERT_TRUE(ast2 == gen2);

    auto ast3 = AST(symbols::ADD,
                    mnum(10),
                    mast(symbols::MULTIPLY, mnum(20), mnum(30)));
    auto gen3 = RepParse::parse("10 + 20 * 30");
    ASSERT_EQ(ast3, gen3);

    auto ast4 = AST(symbols::SUBTRACT,
                    mast(symbols::DIVIDE, mnum(10), mnum(20)),
                    mnum(30));
    auto gen4 = RepParse::parse("10 / 20 - 30");
    ASSERT_EQ(ast4, gen4);
}


TEST(AstParsing, basicWithBrackets) {
    auto ast1 = AST(symbols::SUBTRACT,
                    mast(symbols::DIVIDE, mnum(10), mnum(20)),
                    mnum(30));
    auto gen1 = RepParse::parse("(10 / 20) - 30");
    ASSERT_TRUE(ast1 == gen1);

    auto ast2 = AST(symbols::DIVIDE,
                    mast(symbols::SUBTRACT, mnum(10), mnum(20)),
                    mnum(30));
    auto gen2 = RepParse::parse("(10 - 20) / 30");
    ASSERT_TRUE(ast2 == gen2);

    auto ast3 = AST(symbols::MULTIPLY,
                    mast(symbols::MULTIPLY, mnum(10), mnum(20)),
                    mnum(30));
    auto gen3 = RepParse::parse("(10 * 20) * 30");
    ASSERT_TRUE(ast3 == gen3);

    auto ast4 = AST(symbols::MULTIPLY,
                    mnum(10),
                    mast(symbols::MULTIPLY, mnum(20), mnum(30)));
    auto gen4 = RepParse::parse("10 * (20 * 30)");
    ASSERT_TRUE(ast4 == gen4);

    auto ast5 = AST(symbols::MULTIPLY,
                    mast(symbols::MULTIPLY, mnum(10), mnum(20)),
                    mnum(30));
    auto gen5 = RepParse::parse("10 * (20 * 30)");
    ASSERT_FALSE(ast5 == gen5);
}


TEST(ArgParsing, negateWithSubtract) {
    auto ast1 = AST(symbols::NEGATE,
                    mnum(10));
    auto gen1 = RepParse::parse("-10");
    ASSERT_TRUE(ast1 == gen1);

    auto ast2 = AST(symbols::SUBTRACT,
                    mnum(20),
                    mast(symbols::NEGATE, mnum(10)));
    auto gen2 = RepParse::parse("20 - -10");
    ASSERT_TRUE(ast2 == gen2);
}


TEST(ArgParsing, withFloats) {
    auto ast1 = AST(symbols::SUBTRACT,
                    mast(symbols::DIVIDE, mflo(10), mnum(20)),
                    mflo(7.5));
    auto gen1 = RepParse::parse("(10. / 20) - 7.5");
    ASSERT_TRUE(ast1 == gen1);

    auto ast2 = AST(symbols::SUBTRACT,
                    mast(symbols::DIVIDE, mflo(10), mnum(20)),
                    mflo(7.5));
    auto gen2 = RepParse::parse("(10./20)-7.5");
    ASSERT_TRUE(ast2 == gen2);
}
