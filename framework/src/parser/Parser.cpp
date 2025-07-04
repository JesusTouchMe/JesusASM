// Copyright 2025 JesusTouchMe

#include "JesusASM/Attributes.h"

#include "JesusASM/parser/Parser.h"

#include <filesystem>

namespace JesusASM::parser {
    Parser::Parser(std::string_view fileName, std::vector<lexer::Token>& tokens)
        : mFileName(fileName)
        , mTokens(tokens)
        , mTokenStream(&tokens, &mPosition) {
        mClassModifiers = {
                { lexer::TokenType::PublicKeyword,      MODULEWEB_CLASS_MODIFIER_PUBLIC },
                { lexer::TokenType::PrivateKeyword,     MODULEWEB_CLASS_MODIFIER_PRIVATE },
                { lexer::TokenType::AbstractKeyword,    MODULEWEB_CLASS_MODIFIER_ABSTRACT },
                { lexer::TokenType::FinalKeyword,       MODULEWEB_CLASS_MODIFIER_FINAL },
        };

        mFieldModifiers = {
                { lexer::TokenType::PublicKeyword,      MODULEWEB_FIELD_MODIFIER_PUBLIC },
                { lexer::TokenType::PrivateKeyword,     MODULEWEB_FIELD_MODIFIER_PRIVATE },
                { lexer::TokenType::ProtectedKeyword,   MODULEWEB_FIELD_MODIFIER_PROTECTED },
                { lexer::TokenType::ConstKeyword,       MODULEWEB_FIELD_MODIFIER_CONST },
                { lexer::TokenType::VolatileKeyword,    MODULEWEB_FIELD_MODIFIER_VOLATILE },
        };

        mGlobalVarModifiers = {
                { lexer::TokenType::PublicKeyword,      MODULEWEB_GLOBAL_VAR_MODIFIER_PUBLIC },
                { lexer::TokenType::PrivateKeyword,     MODULEWEB_GLOBAL_VAR_MODIFIER_PRIVATE },
                { lexer::TokenType::VolatileKeyword,    MODULEWEB_GLOBAL_VAR_MODIFIER_VOLATILE },
        };

        mFunctionModifiers = {
                { lexer::TokenType::PublicKeyword,      MODULEWEB_FUNCTION_MODIFIER_PUBLIC },
                { lexer::TokenType::PrivateKeyword,     MODULEWEB_FUNCTION_MODIFIER_PRIVATE },
                { lexer::TokenType::PureKeyword,        MODULEWEB_FUNCTION_MODIFIER_PURE },
                { lexer::TokenType::AsyncKeyword,       MODULEWEB_FUNCTION_MODIFIER_ASYNC },
                { lexer::TokenType::NativeKeyword,      MODULEWEB_FUNCTION_MODIFIER_NATIVE },
        };

        mInstructionParsers = {
                { "nop",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::NOP>(instructions, mLabelList).parse(mTokenStream); } },

                { "add",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::ADD>(instructions, mLabelList).parse(mTokenStream); } },
                { "sub",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::SUB>(instructions, mLabelList).parse(mTokenStream); } },
                { "mul",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::MUL>(instructions, mLabelList).parse(mTokenStream); } },
                { "div",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::DIV>(instructions, mLabelList).parse(mTokenStream); } },
                { "rem",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::REM>(instructions, mLabelList).parse(mTokenStream); } },

                { "and",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::AND>(instructions, mLabelList).parse(mTokenStream); } },
                { "or",             [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::OR>(instructions, mLabelList).parse(mTokenStream); } },
                { "xor",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::XOR>(instructions, mLabelList).parse(mTokenStream); } },
                { "shl",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::SHL>(instructions, mLabelList).parse(mTokenStream); } },
                { "shr",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::SHR>(instructions, mLabelList).parse(mTokenStream); } },

                { "not",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::NOT>(instructions, mLabelList).parse(mTokenStream); } },
                { "neg",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::NEG>(instructions, mLabelList).parse(mTokenStream); } },

                { "dup",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::DUP>(instructions, mLabelList).parse(mTokenStream); } },

                { "swap",           [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::SWAP>(instructions, mLabelList).parse(mTokenStream); } },

                { "load",          [this](auto& instructions) { return InstructionParser<tree::VarInsnNode, Opcodes::LOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "store",         [this](auto& instructions) { return InstructionParser<tree::VarInsnNode, Opcodes::STORE>(instructions, mLabelList).parse(mTokenStream); } },

                { "hload",          [this](auto& instructions) { return InstructionParser<tree::VarInsnNode, Opcodes::HLOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "hstore",         [this](auto& instructions) { return InstructionParser<tree::VarInsnNode, Opcodes::HSTORE>(instructions, mLabelList).parse(mTokenStream); } },

                { "rload",          [this](auto& instructions) { return InstructionParser<tree::VarInsnNode, Opcodes::RLOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "rstore",         [this](auto& instructions) { return InstructionParser<tree::VarInsnNode, Opcodes::RSTORE>(instructions, mLabelList).parse(mTokenStream); } },
                { "rload_0",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::RLOAD_0>(instructions, mLabelList).parse(mTokenStream); } },

                { "baload",         [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::BALOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "bastore",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::BASTORE>(instructions, mLabelList).parse(mTokenStream); } },

                { "caload",         [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::CALOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "castore",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::CASTORE>(instructions, mLabelList).parse(mTokenStream); } },

                { "saload",         [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::SALOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "sastore",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::SASTORE>(instructions, mLabelList).parse(mTokenStream); } },

                { "iaload",         [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::IALOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "iastore",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::IASTORE>(instructions, mLabelList).parse(mTokenStream); } },

                { "laload",         [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::LALOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "lastore",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::LASTORE>(instructions, mLabelList).parse(mTokenStream); } },

                { "haload",         [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::HALOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "hastore",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::HASTORE>(instructions, mLabelList).parse(mTokenStream); } },

                { "raload",         [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::RALOAD>(instructions, mLabelList).parse(mTokenStream); } },
                { "rastore",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::RASTORE>(instructions, mLabelList).parse(mTokenStream); } },

                { "arraylength",    [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::ARRAYLENGTH>(instructions, mLabelList).parse(mTokenStream); } },

                { "new",            [this](auto& instructions) { return InstructionParser<tree::ClassInsnNode, Opcodes::NEW>(instructions, mLabelList).parse(mTokenStream); } },
                { "newarray",       [this](auto& instructions) { return InstructionParser<tree::IntInsnNode, Opcodes::NEWARRAY, tree::OperandSize::BYTE>(instructions, mLabelList).parse(mTokenStream); } },
                { "rnewarray",      [this](auto& instructions) { return InstructionParser<tree::ClassInsnNode, Opcodes::RNEWARRAY>(instructions, mLabelList).parse(mTokenStream); } },

                { "isinstance",     [this](auto& instructions) { return InstructionParser<tree::ClassInsnNode, Opcodes::ISINSTANCE>(instructions, mLabelList).parse(mTokenStream); } },

                { "getfield",       [this](auto& instructions) { return InstructionParser<tree::FieldInsnNode, Opcodes::GETFIELD>(instructions, mLabelList).parse(mTokenStream); } },
                { "setfield",       [this](auto& instructions) { return InstructionParser<tree::FieldInsnNode, Opcodes::SETFIELD>(instructions, mLabelList).parse(mTokenStream); } },

                { "getglobal",      [this](auto& instructions) { return InstructionParser<tree::GlobalVarInsnNode, Opcodes::GETGLOBAL>(instructions, mLabelList).parse(mTokenStream); } },
                { "setglobal",      [this](auto& instructions) { return InstructionParser<tree::GlobalVarInsnNode, Opcodes::SETGLOBAL>(instructions, mLabelList).parse(mTokenStream); } },

                { "jmp_cmpeq",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_CMPEQ>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp_cmpne",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_CMPNE>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp_cmplt",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_CMPLT>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp_cmpgt",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_CMPGT>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp_cmple",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_CMPLE>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp_cmpge",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_CMPGE>(instructions, mLabelList).parse(mTokenStream); } },

                { "jmp_hcmpeq",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_HCMPEQ>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp_hcmpne",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_HCMPNE>(instructions, mLabelList).parse(mTokenStream); } },

                { "jmp_rcmpeq",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_RCMPEQ>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp_rcmpne",     [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_RCMPNE>(instructions, mLabelList).parse(mTokenStream); } },

                { "jmp_hnull",      [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_HNULL>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp_hnonnull",   [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_HNONNULL>(instructions, mLabelList).parse(mTokenStream); } },

                { "jmp_rnull",      [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_RNULL>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp_rnonnull",   [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP_RNONNULL>(instructions, mLabelList).parse(mTokenStream); } },

                { "jmpeq",          [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMPEQ>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmpne",          [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMPNE>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmplt",          [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMPLT>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmpgt",          [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMPGT>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmple",          [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMPLE>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmpge",          [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMPGE>(instructions, mLabelList).parse(mTokenStream); } },
                { "jmp",            [this](auto& instructions) { return InstructionParser<tree::JumpInsnNode, Opcodes::JMP>(instructions, mLabelList).parse(mTokenStream); } },

                { "cmp",           [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::CMP>(instructions, mLabelList).parse(mTokenStream); } },
                { "hcmp",           [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::HCMP>(instructions, mLabelList).parse(mTokenStream); } },
                { "rcmp",           [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::RCMP>(instructions, mLabelList).parse(mTokenStream); } },

                { "bpush",          [this](auto& instructions) { return InstructionParser<tree::IntInsnNode, Opcodes::BPUSH, tree::OperandSize::BYTE>(instructions, mLabelList).parse(mTokenStream); } },
                { "spush",          [this](auto& instructions) { return InstructionParser<tree::IntInsnNode, Opcodes::SPUSH, tree::OperandSize::SHORT>(instructions, mLabelList).parse(mTokenStream); } },
                { "ipush",          [this](auto& instructions) { return InstructionParser<tree::IntInsnNode, Opcodes::IPUSH, tree::OperandSize::INT>(instructions, mLabelList).parse(mTokenStream); } },
                { "lpush",          [this](auto& instructions) { return InstructionParser<tree::IntInsnNode, Opcodes::LPUSH, tree::OperandSize::LONG>(instructions, mLabelList).parse(mTokenStream); } },

                { "l2b",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::L2B>(instructions, mLabelList).parse(mTokenStream); } },
                { "l2s",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::L2S>(instructions, mLabelList).parse(mTokenStream); } },
                { "l2i",            [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::L2I>(instructions, mLabelList).parse(mTokenStream); } },

                { "const_m1",       [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::CONST_M1>(instructions, mLabelList).parse(mTokenStream); } },
                { "const_0",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::CONST_0>(instructions, mLabelList).parse(mTokenStream); } },
                { "const_1",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::CONST_1>(instructions, mLabelList).parse(mTokenStream); } },

                { "hconst_null",    [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::HCONST_NULL>(instructions, mLabelList).parse(mTokenStream); } },

                { "rconst_null",    [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::RCONST_NULL>(instructions, mLabelList).parse(mTokenStream); } },

                { "call",           [this](auto& instructions) { return InstructionParser<tree::CallInsnNode, Opcodes::CALL>(instructions, mLabelList).parse(mTokenStream); } },

                { "return",         [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::RETURN>(instructions, mLabelList).parse(mTokenStream); } },
                { "lreturn",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::LRETURN>(instructions, mLabelList).parse(mTokenStream); } },
                { "hreturn",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::HRETURN>(instructions, mLabelList).parse(mTokenStream); } },
                { "rreturn",        [this](auto& instructions) { return InstructionParser<tree::InsnNode, Opcodes::RRETURN>(instructions, mLabelList).parse(mTokenStream); } },

                { "ldc",            [this](auto& instructions) { return InstructionParser<tree::LdcInsnNode, Opcodes::LDC>(instructions, mLabelList).parse(mTokenStream); } },
        };
    }

    std::unique_ptr<tree::ModuleNode> Parser::parse() {
        auto module = std::make_unique<tree::ModuleNode>();
        mModule = module.get();

        module->version = 1;
        module->name = std::filesystem::path(mFileName).replace_extension().string();

        // (technically) nonstandard attributes used to help debugging and reverse engineering tools determine how a module was compiled
        module->attributes.push_back(std::make_unique<Attribute<std::string_view>>("CompilerID", "JesusASM 1.0"));

        while (current().getTokenType() != lexer::TokenType::EndOfFile) {
            populateModule();
        }

        return module;
    }

    bool Parser::isModifier() {
        auto type = current().getTokenType();
        return type == lexer::TokenType::AbstractKeyword || type == lexer::TokenType::AsyncKeyword
                || type == lexer::TokenType::ConstKeyword || type == lexer::TokenType::FinalKeyword
                || type == lexer::TokenType::NativeKeyword || type == lexer::TokenType::PublicKeyword
                || type == lexer::TokenType::PrivateKeyword || type == lexer::TokenType::ProtectedKeyword
                || type == lexer::TokenType::PureKeyword || type == lexer::TokenType::VolatileKeyword;
    }

    bool Parser::isFieldModifier() {
        auto type = current().getTokenType();
        return mFieldModifiers.contains(type);
    }

    void Parser::populateModule() {
        std::vector<lexer::TokenType> modifiers;

        while (isModifier()) {
            modifiers.push_back(consume().getTokenType());
        }

        lexer::Token token = current();

        switch (token.getTokenType()) {
            case lexer::TokenType::AttributeKeyword:
                if (!modifiers.empty()) {
                    std::cout << "weird attribute\n";
                    std::exit(1);
                }

                mModule->attributes.push_back(parseAttribute());
                break;

            case lexer::TokenType::ClassKeyword:
                mModule->classes.push_back(parseClass(modifiers));
                break;

            case lexer::TokenType::GlobalKeyword:
                mModule->globals.push_back(parseGlobalVar(modifiers));
                break;

            case lexer::TokenType::Type:
            case lexer::TokenType::Identifier:
                mModule->functions.push_back(parseFunction(modifiers));
                break;

            default:
                std::cout << "erm\n";
                std::exit(1);
        }
    }

    Type* Parser::parseType() {
        Type* type;
        if (current().getTokenType() == lexer::TokenType::Type) {
            type = Type::GetBuiltinType(consume().getText());
        } else {
            std::string moduleName(consume().getText());

            while (current().getTokenType() != lexer::TokenType::Colon) {
                expectToken(lexer::TokenType::Slash);
                consume();

                expectToken(lexer::TokenType::Identifier);

                moduleName += '/';
                moduleName += consume().getText();
            }

            consume(); // :

            expectToken(lexer::TokenType::Identifier);
            std::string className(consume().getText());

            type = Type::GetClassType(moduleName, className);
        }

        while (current().getTokenType() == lexer::TokenType::LeftBracket) {
            consume();
            expectToken(lexer::TokenType::RightBracket);
            consume();

            type = Type::GetArrayType(type);
        }

        return type;
    }

    std::unique_ptr<IAttribute> Parser::parseAttribute() {
        consume(); // attribute

        mTokenStream.expectAny(lexer::TokenType::Identifier, lexer::TokenType::StringLiteral);
        std::string name(consume().getText());

        expectToken(lexer::TokenType::LeftBrace);
        consume();

        if (name == "RequiredPlugins") {
            RequiredPluginsAttribute attribute;

            while (current().getTokenType() != lexer::TokenType::RightBrace) {
                expectToken(lexer::TokenType::StringLiteral);
                std::string value(consume().getText());

                if (current().getTokenType() != lexer::TokenType::RightBrace) {
                    expectToken(lexer::TokenType::Comma);
                    consume();
                }

                attribute.value.push_back(std::move(value));
            }
            consume();

            return std::make_unique<Attribute<RequiredPluginsAttribute>>(attribute);
        }
    }

    std::unique_ptr<tree::ClassNode> Parser::parseClass(const std::vector<lexer::TokenType>& classModifiers) {
        consume(); // class

        auto clas = std::make_unique<tree::ClassNode>();

        clas->attributes.push_back(std::make_unique<Attribute<bool>>("PreSortedFields", false));

        for (auto modifier : classModifiers) {
            auto it = mClassModifiers.find(modifier);
            if (it == mClassModifiers.end()) {
                std::cout << "weird class modifier detected: "
                << lexer::Token("", modifier, lexer::SourceLocation(), lexer::SourceLocation()).getName()
                << "\n";
                std::exit(1);
            }

            clas->modifiers |= it->second;
        }

        expectToken(lexer::TokenType::Identifier);
        clas->name = consume().getText();

        if (current().getTokenType() == lexer::TokenType::ExtendsKeyword) {
            consume();
            Type* superClass = parseType();

            if (superClass->getDescriptor()[0] != 'R') {
                std::cout << "Bad supertype\n";
                std::exit(1);
            }

            clas->superClass = superClass->getName();
        }

        expectToken(lexer::TokenType::LeftBrace);
        consume();

        while (current().getTokenType() != lexer::TokenType::RightBrace) {
            u16 modifiers = 0;
            while (isFieldModifier()) {
                modifiers |= mFieldModifiers[consume().getTokenType()];
            }

            Type* type = parseType();

            expectToken(lexer::TokenType::Identifier);
            std::string_view name = consume().getText();

            expectToken(lexer::TokenType::Semicolon);
            consume();

            clas->fields.push_back(std::make_unique<tree::FieldNode>(modifiers, name, type->getDescriptor()));
        }
        consume();

        return std::move(clas);
    }

    std::unique_ptr<tree::GlobalVarNode> Parser::parseGlobalVar(const std::vector<lexer::TokenType>& modifiers) {
        consume(); // global

        auto global = std::make_unique<tree::GlobalVarNode>();

        for (auto modifier : modifiers) {
            auto it = mGlobalVarModifiers.find(modifier);
            if (it == mGlobalVarModifiers.end()) {
                std::cout << "weird global modifier detected: "
                          << lexer::Token("", modifier, lexer::SourceLocation(), lexer::SourceLocation()).getName()
                          << "\n";
                std::exit(1);
            }

            global->modifiers |= it->second;
        }

        Type* type = parseType();

        expectToken(lexer::TokenType::Identifier);
        global->name = consume().getText();
        global->descriptor = type->getDescriptor();

        expectToken(lexer::TokenType::Semicolon);
        consume();

        return global;
    }

    std::unique_ptr<tree::FunctionNode> Parser::parseFunction(const std::vector<lexer::TokenType>& modifiers) {
        auto function = std::make_unique<tree::FunctionNode>();

        function->modifiers = 0;

        for (auto modifier : modifiers) {
            auto it = mFunctionModifiers.find(modifier);
            if (it == mFunctionModifiers.end()) {
                std::cout << "weird function modifier detected: "
                          << lexer::Token("", modifier, lexer::SourceLocation(), lexer::SourceLocation()).getName()
                          << "\n";
                std::exit(1);
            }

            function->modifiers |= it->second;
        }

        Type* returnType = parseType();
        Type* implicitArgument = nullptr;

        std::string name;

        if (peek(1).getTokenType() == lexer::TokenType::DoubleColon) {
            expectToken(lexer::TokenType::Identifier);
            std::string_view className = consume().getText();
            name += className;
            name += "::";

            implicitArgument = Type::GetClassType(mModule->name, className);

            consume(); // ::
        }

        if (current().getTokenType() == lexer::TokenType::Hash) {
            name += "#";
            consume();
        }

        expectToken(lexer::TokenType::Identifier);
        name += consume().getText();

        function->name = std::move(name);

        expectToken(lexer::TokenType::LeftParen);
        consume();

        std::vector<Type*> args;

        if (implicitArgument != nullptr) {
            args.push_back(implicitArgument);
        }

        while (current().getTokenType() != lexer::TokenType::RightParen) {
            Type* type = parseType();
            args.push_back(type);

            if (current().getTokenType() != lexer::TokenType::RightParen) {
                expectToken(lexer::TokenType::Comma);
                consume();
            }
        }
        consume();

        Type* functionType = Type::GetFunctionType(returnType, args);
        function->descriptor = functionType->getDescriptor();

        if (function->modifiers & MODULEWEB_FUNCTION_MODIFIER_NATIVE) {
            expectToken(lexer::TokenType::Semicolon);
            consume();
            return std::move(function);
        }

        function->attributes.push_back(std::make_unique<Attribute<bool>>("CompilerOptimized", false));

        //TODO: support simple function definitions

        expectToken(lexer::TokenType::LeftBrace);
        consume();

        while (current().getTokenType() != lexer::TokenType::RightBrace) {
            parseFunctionBody(function.get());
        }
        consume();

        return std::move(function);
    }

    void Parser::parseFunctionBody(tree::FunctionNode* function) {
        if (current().getTokenType() == lexer::TokenType::AttributeKeyword) {
            consume(); // even though function bodies are implicitly attributes, there's no harm in explicitly saying it's one
        }

        expectToken(lexer::TokenType::Identifier);
        std::string bodyName(consume().getText());

        if (bodyName == "Code") {
            expectToken(lexer::TokenType::LeftBrace);
            consume();

            while (current().getTokenType() != lexer::TokenType::RightBrace) {
                if (current().getTokenType() == lexer::TokenType::Identifier) {
                    std::string name(consume().getText());

                    expectToken(lexer::TokenType::Colon);
                    consume();

                    auto label = mLabelList.removeLabel(name);
                    if (label != nullptr) {
                        function->instructions.add(std::move(label));
                    } else {
                        function->instructions.add(std::make_unique<tree::LabelNode>(name));
                    }
                } else {
                    expectToken(lexer::TokenType::Instruction);
                    std::string_view instruction = consume().getText();

                    auto it = mInstructionParsers.find(instruction);
                    if (it == mInstructionParsers.end()) {
                        std::cout << "Unable to parse instruction: " << instruction << "\n";
                        std::exit(1);
                    }

                    function->instructions.add(it->second(function->instructions));
                }
            }
            consume();
        } else {
            expectToken(lexer::TokenType::LeftBrace);
            consume();

            std::vector<u8> bytes;

            while (current().getTokenType() != lexer::TokenType::RightBrace) {
                expectToken(lexer::TokenType::IntegerLiteral);

                std::string stupidLanguage(consume().getText());
                u8 value = static_cast<u8>(std::stol(stupidLanguage));

                bytes.push_back(value);
            }
            consume();

            function->attributes.push_back(std::make_unique<Attribute<u8*>>(bodyName, bytes.data(), bytes.size()));
        }
    }
}