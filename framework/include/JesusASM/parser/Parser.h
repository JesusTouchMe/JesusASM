// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_PARSER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_PARSER_H

#include "JesusASM/lexer/Token.h"

#include "JesusASM/parser/InstructionParser.h"

#include "JesusASM/tree/ModuleNode.h"

#include <functional>
#include <unordered_map>
#include <vector>

namespace JesusASM::parser {
    // Parses the tokens gathered from a file into a single ModuleNode
    class Parser {
    public:
        Parser(std::string_view fileName, std::vector<lexer::Token>& tokens);

        std::unique_ptr<tree::ModuleNode> parse();

    private:
        std::string_view mFileName;
        std::vector<lexer::Token>& mTokens;
        std::size_t mPosition = 0;

        TokenStream mTokenStream;

        tree::InsnList mLabelList;

        tree::ModuleNode* mModule;

        std::unordered_map<lexer::TokenType, u16> mClassModifiers;
        std::unordered_map<lexer::TokenType, u16> mFieldModifiers;
        std::unordered_map<lexer::TokenType, u16> mFunctionModifiers;

        std::unordered_map<std::string_view, std::function<std::unique_ptr<tree::AbstractInsnNode>(tree::InsnList& instructions)>> mInstructionParsers;

        lexer::Token& current() { return mTokenStream.current(); }
        lexer::Token& consume() { return mTokenStream.consume(); }
        lexer::Token& peek(i32 offset) { return mTokenStream.peek(offset); }
        void expectToken(lexer::TokenType type) { mTokenStream.expect(type); }

        bool isModifier();

        bool isFieldModifier();

        void populateModule();

        Type* parseType();

        std::unique_ptr<IAttribute> parseAttribute();
        std::unique_ptr<tree::ClassNode> parseClass(const std::vector<lexer::TokenType>& modifiers);
        std::unique_ptr<tree::FunctionNode> parseFunction(const std::vector<lexer::TokenType>& modifiers);

        void parseFunctionBody(tree::FunctionNode* function);
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_PARSER_H
