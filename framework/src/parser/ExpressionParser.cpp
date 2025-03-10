// Copyright 2025 JesusTouchMe

#include "JesusASM/parser/ExpressionParser.h"

namespace JesusASM::parser {
    i64 ExpressionParser::parse(TokenStream tokens) {
        mTokens = tokens;
        return parseExpression();
    }

    int ExpressionParser::getBinaryOperatorPrecedence(lexer::TokenType type) {
        switch (type) {
            case lexer::TokenType::LeftParen:
                return 90;

            case lexer::TokenType::Star:
            case lexer::TokenType::Slash:
                return 75;

            case lexer::TokenType::Plus:
            case lexer::TokenType::Minus:
                return 70;

            default:
                return 0;
        }
    }

    int ExpressionParser::getUnaryOperatorPrecedence(lexer::TokenType type) {
        switch (type) {
            case lexer::TokenType::Plus:
            case lexer::TokenType::Minus:
            case lexer::TokenType::LeftParen:
                return 85;

            default:
                return 0;
        }
    }

    i64 ExpressionParser::parseExpression(int precedence) {
        i64 lhs;
        int unaryOperatorPrecedence = getUnaryOperatorPrecedence(mTokens.current().getTokenType());

        if (unaryOperatorPrecedence >= precedence) {
            lexer::Token operatorToken = mTokens.consume();

            switch (operatorToken.getTokenType()) {
                case lexer::TokenType::Plus:
                    lhs = +parseExpression(unaryOperatorPrecedence);
                    break;
                case lexer::TokenType::Minus:
                    lhs = -parseExpression(unaryOperatorPrecedence);
                    break;
                case lexer::TokenType::LeftParen:
                    lhs = parseParenExpression();
                    break;

                default:
                    std::cout << "unreacabl\n";
                    std::exit(1);
            }
        } else {
            lhs = parsePrimary();
        }

        while(true) {
            int binaryOperatorPrecedence = getBinaryOperatorPrecedence(mTokens.current().getTokenType());
            if (binaryOperatorPrecedence < precedence) {
                break;
            }

            i64 rhs;
            lexer::Token operatorToken = mTokens.consume();

            switch (operatorToken.getTokenType()) {
                case lexer::TokenType::Plus:
                    rhs = parseExpression(binaryOperatorPrecedence);
                    lhs += rhs;
                    break;

                case lexer::TokenType::Minus:
                    rhs = parseExpression(binaryOperatorPrecedence);
                    lhs -= rhs;
                    break;

                case lexer::TokenType::Star:
                    rhs = parseExpression(binaryOperatorPrecedence);
                    lhs *= rhs;
                    break;

                case lexer::TokenType::Slash:
                    rhs = parseExpression(binaryOperatorPrecedence);
                    lhs /= rhs;
                    break;

                default:
                    std::cout << "unrechlable\n";
                    std::exit(1);
            }
        }

        return lhs;
    }

    i64 ExpressionParser::parsePrimary() {
        switch (mTokens.current().getTokenType()) {
            case lexer::TokenType::IntegerLiteral:
                return parseIntegerLiteral();

            default:
                std::cout << "erm\n";
                std::exit(1);
        }
    }

    i64 ExpressionParser::parseParenExpression() {
        i64 expr = parseExpression();

        mTokens.expect(lexer::TokenType::RightParen);
        mTokens.consume();

        return expr;
    }

    i64 ExpressionParser::parseIntegerLiteral() {
        std::string tmp(mTokens.consume().getText());
        return std::stoll(tmp);
    }
}