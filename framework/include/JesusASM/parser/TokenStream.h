// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_TOKENSTREAM_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_TOKENSTREAM_H

#include "moduleweb/types.h"

#include "JesusASM/lexer/Token.h"

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
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_TOKENSTREAM_H
