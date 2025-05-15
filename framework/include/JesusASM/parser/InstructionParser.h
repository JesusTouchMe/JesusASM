// Copyright 2025 JesusTouchMe

// Design shamelessly stolen from vasm (https://github.com/viper-org/vasm/blob/master/framework/include/vasm/instruction/Builder.h)
// Adapted to JesusASM design

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_INSTRUCTIONPARSER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_INSTRUCTIONPARSER_H

#include "JesusASM/lexer/Token.h"

#include "JesusASM/parser/ExpressionParser.h"
#include "JesusASM/parser/TokenStream.h"

#include "JesusASM/tree/AbstractInsnNode.h"
#include "JesusASM/tree/InsnList.h"

#include "JesusASM/tree/instructions/CallInsnNode.h"
#include "JesusASM/tree/instructions/ClassInsnNode.h"
#include "JesusASM/tree/instructions/FieldInsnNode.h"
#include "JesusASM/tree/instructions/GlobalVarInsnNode.h"
#include "JesusASM/tree/instructions/InsnNode.h"
#include "JesusASM/tree/instructions/IntInsnNode.h"
#include "JesusASM/tree/instructions/JumpInsnNode.h"
#include "JesusASM/tree/instructions/LdcInsnNode.h"
#include "JesusASM/tree/instructions/VarInsnNode.h"

#include "JesusASM/type/Type.h"

#include <format>
#include <iostream>
#include <vector>

namespace JesusASM::parser {
    struct GenericTargetSymbol {
        std::string module;
        std::string name;
        std::string descriptor;
    };

    struct FieldTarget {
        Name owner;
        std::string name;
        std::string descriptor;
    };

    using CallTarget = GenericTargetSymbol;
    using GlobalVarTarget = GenericTargetSymbol;

    template<class Insn, Opcode opcode, tree::OperandSize operandSize = tree::OperandSize::INT>
    class InstructionParser {
    public:
        InstructionParser(tree::InsnList& instructions, tree::InsnList& labelList)
            : mInstructions(instructions)
            , mLabelList(labelList) {}

        std::unique_ptr<Insn> parse(TokenStream tokens) {
            mTokens = tokens;

            if constexpr (std::derived_from<Insn, tree::InsnNode>) {
                return std::make_unique<Insn>(opcode);
            } else if constexpr (std::derived_from<Insn, tree::CallInsnNode>) {
                CallTarget target = parseCallTarget();
                return std::make_unique<Insn>(opcode, std::move(target.module), std::move(target.name), std::move(target.descriptor));
            } else if constexpr (std::derived_from<Insn, tree::ClassInsnNode>) {
                Type* type = parseType();
                return std::make_unique<Insn>(opcode, type->getName());
            } else if constexpr (std::derived_from<Insn, tree::FieldInsnNode>) {
                FieldTarget target = parseFieldTarget();
                return std::make_unique<Insn>(opcode, target.owner, target.name, target.descriptor);
            } else if constexpr (std::derived_from<Insn, tree::GlobalVarInsnNode>) {
                GlobalVarTarget target = parseGlobalVarTarget();
                return std::make_unique<Insn>(opcode, target.module, target.name, target.descriptor);
            } else if constexpr (std::derived_from<Insn, tree::IntInsnNode>) {
                i64 value = parseInt();
                return std::make_unique<Insn>(opcode, operandSize, value);
            } else if constexpr (std::derived_from<Insn, tree::JumpInsnNode>) {
                tree::LabelNode* label = parseLabel();
                return std::make_unique<Insn>(opcode, label);
            } else if constexpr (std::derived_from<Insn, tree::VarInsnNode>) {
                i64 number = parseInt();
                if (number < 0 || number >= 0xFFFF) {
                    std::cout << "Too big or too small index for variable operand. Expected index between 0x0-0xFFFF\n";
                    std::exit(1);
                }

                u16 index = static_cast<u16>(number);

                return std::make_unique<Insn>(opcode, index);
            } else if constexpr (std::derived_from<Insn, tree::LdcInsnNode>) {
                mTokens.expect(lexer::TokenType::StringLiteral); // for now this is string only
                std::string value(mTokens.consume().getText());

                return std::make_unique<Insn>(std::move(value));
            } else {
                static_assert(false, "Unsupported Insn type");
            }
        }

    private:
        tree::InsnList& mInstructions;
        tree::InsnList& mLabelList;
        TokenStream mTokens;

        Type* parseType() {
            Type* type;
            if (mTokens.current().getTokenType() == lexer::TokenType::Type) {
                type = Type::GetBuiltinType(mTokens.consume().getText());
            } else {
                std::string moduleName(mTokens.consume().getText());

                while (mTokens.current().getTokenType() != lexer::TokenType::Colon) {
                    mTokens.expect(lexer::TokenType::Slash);
                    mTokens.consume();

                    mTokens.expect(lexer::TokenType::Identifier);

                    moduleName += '/';
                    moduleName += mTokens.consume().getText();
                }

                mTokens.consume(); // :

                mTokens.expect(lexer::TokenType::Identifier);
                std::string className(mTokens.consume().getText());

                type = Type::GetClassType(moduleName, className);
            }

            while (mTokens.current().getTokenType() == lexer::TokenType::LeftBracket) {
                mTokens.consume();
                mTokens.expect(lexer::TokenType::RightBracket);
                mTokens.consume();

                type = Type::GetArrayType(type);
            }

            return type;
        }

        std::string parseModuleName() {
            std::string name(mTokens.consume().getText());

            while (mTokens.current().getTokenType() == lexer::TokenType::Slash) {
                mTokens.consume();
                name += '/';

                mTokens.expect(lexer::TokenType::Identifier);
                name += mTokens.consume().getText();
            }

            return name;
        }

        CallTarget parseCallTarget() {
            CallTarget target;

            mTokens.expect(lexer::TokenType::Identifier);
            target.module = parseModuleName();

            mTokens.expect(lexer::TokenType::Colon);
            mTokens.consume();

            Type* implicitArgument = nullptr;

            target.name = "";

            if (mTokens.peek(1).getTokenType() == lexer::TokenType::DoubleColon) {
                mTokens.expect(lexer::TokenType::Identifier);
                std::string_view className = mTokens.consume().getText();
                target.name += className;
                target.name += "::";

                implicitArgument = Type::GetClassType(target.module, className);

                mTokens.consume(); // ::
            }

            if (mTokens.current().getTokenType() == lexer::TokenType::Hash) {
                target.name += "#";
                mTokens.consume();
            }

            mTokens.expect(lexer::TokenType::Identifier);
            target.name += mTokens.consume().getText();

            mTokens.expect(lexer::TokenType::Colon);
            mTokens.consume();

            std::string descriptor = "(";
            Type* returnType = parseType();

            mTokens.expect(lexer::TokenType::LeftParen);
            mTokens.consume();

            if (implicitArgument != nullptr) {
                descriptor += implicitArgument->getDescriptor();
            }

            while (mTokens.current().getTokenType() != lexer::TokenType::RightParen) {
                Type* arg = parseType();

                descriptor += arg->getDescriptor();

                if (mTokens.current().getTokenType() != lexer::TokenType::RightParen) {
                    mTokens.expect(lexer::TokenType::Comma);
                    mTokens.consume();
                }
            }
            mTokens.consume();

            descriptor += ')';
            descriptor += returnType->getDescriptor();

            target.descriptor = std::move(descriptor);

            return target;
        }

        FieldTarget parseFieldTarget() {
            FieldTarget target;

            Type* type = parseType();
            if (type->getDescriptor()[0] != 'R') {
                std::cout << "Bad type for field\n";
                std::exit(1);
            }

            target.owner = type->getName();

            mTokens.expect(lexer::TokenType::Colon);
            mTokens.consume();

            mTokens.expect(lexer::TokenType::Identifier);
            target.name = mTokens.consume().getText();

            mTokens.expect(lexer::TokenType::Colon);
            mTokens.consume();

            type = parseType();
            target.descriptor = type->getDescriptor();

            return target;
        }

        GlobalVarTarget parseGlobalVarTarget() {
            GlobalVarTarget target;

            mTokens.expect(lexer::TokenType::Identifier);
            target.module = parseModuleName();

            mTokens.expect(lexer::TokenType::Colon);
            mTokens.consume();

            mTokens.expect(lexer::TokenType::Identifier);
            target.name = mTokens.consume().getText();

            mTokens.expect(lexer::TokenType::Colon);
            mTokens.consume();

            Type* type = parseType();
            target.descriptor = type->getDescriptor();

            return target;
        }

        i64 parseInt() {
            ExpressionParser parser{};
            return parser.parse(mTokens);
        }

        tree::LabelNode* parseLabel() {
            mTokens.expect(lexer::TokenType::Identifier);
            std::string_view name = mTokens.consume().getText();

            tree::LabelNode* label = mLabelList.findLabel(name);
            if (label != nullptr) {
                return label;
            }

            label = mInstructions.findLabel(name);
            if (label != nullptr) {
                return label;
            }

            mLabelList.add(std::make_unique<tree::LabelNode>(name));
            return static_cast<tree::LabelNode*>(mLabelList.getLast());
        }
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_PARSER_INSTRUCTIONPARSER_H
