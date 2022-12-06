add_library(RepParseLib STATIC
        Tokenizer.h Tokenizer.cpp
        RepParse.h RepParse.cpp
        tree/AST.h
        token/Operator.h
        token/Token.h
        token/Binary.h
        token/Unary.h
        token/NumericToken.h
        token/End.h
        token/Sentinel.h
        token/Brackets.h
        token/Compare.h
        token/Symbols.h
        utils/Utils.h
        token/NumberVariant.h)
