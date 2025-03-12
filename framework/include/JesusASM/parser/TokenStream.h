// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_TOKENSTREAM_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_TOKENSTREAM_H

#include "moduleweb/types.h"

#include "JesusASM/lexer/Token.h"

#include <concepts>
#include <format>
#include <iostream>
#include <vector>

namespace JesusASM::parser {
    struct TokenStream {
        std::vector<lexer::Token>* tokens;
        std::size_t* position;

        lexer::Token& current() { return tokens->at(*position); }

        lexer::Token& consume() { return tokens->at((*position)++); }

        lexer::Token& peek(i32 offset) { return tokens->at(*position + offset); }

        void expect(lexer::TokenType type) {
            if (current().getTokenType() != type) {
                lexer::Token temp("", type, lexer::SourceLocation(), lexer::SourceLocation());
                std::cout << std::format("{}:{}:{} error: Expected '{}', found '{}'\n",
                                         current().getStartLocation().file, current().getStartLocation().line,
                                         current().getStartLocation().col, temp.getName(), current().getText());
                std::exit(1);
            }
        }

        constexpr void expectAny(lexer::TokenType first, auto... rest) {
            if constexpr (sizeof...(rest) == 0) {
                if (current().getTokenType() == first)
                    return;
            } else {
                if (((current().getTokenType() == first) || ... || (current().getTokenType() == rest)))
                    return;
            }

            std::string tokensString;
            auto appendToken = [&](lexer::TokenType type) {
                lexer::Token temp("", type, lexer::SourceLocation(), lexer::SourceLocation());
                tokensString += std::format("'{}', ", temp.getName());
            };

            appendToken(first);
            (appendToken(rest), ...);

            tokensString = tokensString.substr(0, tokensString.size() - 2);

            std::cout << std::format("{}:{}:{} error: Expected either {}, found '{}'\n",
                                     current().getStartLocation().file, current().getStartLocation().line,
                                     current().getStartLocation().col, tokensString, current().getText());
            std::exit(1);
        }
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_TOKENSTREAM_H
