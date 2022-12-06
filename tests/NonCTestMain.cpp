//
// Created by max on 29/11/22.
//

#include "token/NumberVariant.h"
#include "tree/AST.h"
#include "RepParse.h"

using namespace repper;
using namespace std;

int main() {
    auto ten = make_shared<AST>(AST(TypedNumbers((int64_t) 10)));
    auto twenty = make_shared<AST>(AST(TypedNumbers((int64_t) 20)));

    auto ast = AST(symbols::ADD, ten, twenty);
    auto genAst = RepParse::parse("10 + 20");
    auto test = genAst == ast;
}
