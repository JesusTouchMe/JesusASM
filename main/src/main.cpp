// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/ModuleNode.h"

#include "JesusASM/lexer/Lexer.h"
#include "JesusASM/lexer/Token.h"

#include "JesusASM/parser/Parser.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

std::string WideToString(const std::wstring& wstr) {
    std::size_t size = std::wcstombs(nullptr, wstr.c_str(), 0);
    if (size == static_cast<std::size_t>(-1)) {
        throw std::runtime_error("Invalid wide string conversion");
    }

    std::string str(size, '\0');
    std::wcstombs(&str[0], wstr.c_str(), size);
    return str;
}

int main(int argc, char** argv) {
    JesusASM::Type::Init();

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        std::filesystem::path file = arg;
        std::string fileName = WideToString(file.wstring());

        if (!file.has_extension()) {
            file.replace_extension(".jasm");
        }

        std::ifstream input(file);
        std::stringstream buffer;
        buffer << input.rdbuf();

        std::string text = buffer.str();

        JesusASM::lexer::Lexer lexer(text, fileName);

        std::vector<JesusASM::lexer::Token> tokens = lexer.lex();

        JesusASM::parser::Parser parser(fileName, tokens);
        std::unique_ptr<JesusASM::tree::ModuleNode> module = parser.parse();

        moduleweb::ModuleBuilder builder;
        moduleweb::ModuleInfo info;

        module->emit(builder, info);

        info.print();

        std::filesystem::path outFile = "out" / file;
        outFile.replace_extension(".jmod");
        std::string fileName2 = WideToString(outFile.wstring());

        std::filesystem::create_directories(outFile.parent_path());

        moduleweb::FileOutStream out(fileName2);
        info.emit(out);
    }

    return 0;
}