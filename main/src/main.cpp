// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/ModuleNode.h"

#include "JesusASM/lexer/Lexer.h"
#include "JesusASM/lexer/Token.h"

#include "JesusASM/parser/Parser.h"

#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
    JesusASM::Type::Init();

    std::ifstream input("Main.jasm");
    std::stringstream buffer;
    buffer << input.rdbuf();

    std::string text = buffer.str();

    lexer::Lexer lexer(text, "Main.jasm");

    std::vector<lexer::Token> tokens = lexer.lex();

    JesusASM::parser::Parser parser("Main.jasm", tokens);
    std::unique_ptr<JesusASM::tree::ModuleNode> module = parser.parse();

    moduleweb::ModuleBuilder builder;
    moduleweb::ModuleInfo info;

    module->emit(builder, info);

    info.print();

    moduleweb::FileOutStream out("Main.jmod");
    info.emit(out);

    return 0;
}