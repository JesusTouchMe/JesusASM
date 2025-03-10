// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_EXPRESSIONPARSER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_EXPRESSIONPARSER_H

#include "JesusASM/parser/TokenStream.h"

namespace JesusASM::parser {
    class ExpressionParser {
    public:
        i64 parse(TokenStream tokens);

    private:
        TokenStream mTokens;

        int getBinaryOperatorPrecedence(lexer::TokenType type);
        int getUnaryOperatorPrecedence(lexer::TokenType type);

        i64 parseExpression(int precedence = 1);
        i64 parsePrimary();

        i64 parseParenExpression();

        i64 parseIntegerLiteral();
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_EXPRESSIONPARSER_H
