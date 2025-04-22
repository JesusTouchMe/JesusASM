// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/CallInsnNode.h"

#include <format>
#include <stdexcept>

namespace JesusASM::tree {
    CallInsnNode::CallInsnNode(Opcode opcode, std::string_view module, std::string_view name,std::string_view descriptor)
        : AbstractInsnNode(InsnType::CALL, opcode)
        , mModule(module)
        , mName(name)
        , mDescriptor(descriptor) {}

    CallInsnNode::CallInsnNode(Opcode opcode, std::string&& module, std::string&& name, std::string&& descriptor)
        : AbstractInsnNode(InsnType::CALL, opcode)
        , mModule(std::move(module))
        , mName(std::move(name))
        , mDescriptor(std::move(descriptor)) {}

    int CallInsnNode::getStackPushes() const {
        auto pos = mDescriptor.rfind(')');
        if (pos == std::string_view::npos) {
            throw std::runtime_error("Bad descriptor");
        }

        char c = mDescriptor[pos + 1];
        switch (c) {
            case 'V':
                return 0;

            case 'B':
            case 'S':
            case 'I':
            case 'C':
            case 'Z':
                return 1;

            case 'R':
            case '[':
            case 'H':
            case 'L':
            case 'D':
                return 2;

            default:
                throw std::runtime_error("Bad descriptor");
        }
    }

    int CallInsnNode::getStackPops() const {
        if (mDescriptor.front() != '(') {
            throw std::runtime_error("bad descriptor");
        }

        int arguments = 0;

        size_t i = 1;
        while (i < mDescriptor.size() && mDescriptor[i] != ')') {
            char c = mDescriptor[i];

            switch (c) {
                case 'B':
                case 'S':
                case 'I':
                case 'C':
                case 'Z':
                case 'F':
                    arguments += 1;
                    i++;
                    break;

                case 'L':
                case 'D':
                    arguments += 2;
                    i++;
                    break;

                case 'R': {
                    size_t semicolon = mDescriptor.find(';', i);
                    if (semicolon == std::string_view::npos) {
                        throw std::invalid_argument("Unterminated object type in descriptor");
                    }

                    arguments += 2;
                    i = semicolon + 1;

                    break;
                }

                case '[': {
                    while (mDescriptor[i] == '[')
                        i++;

                    if (mDescriptor[i] == 'R') {
                        size_t semicolon = mDescriptor.find(';', i);
                        if (semicolon == std::string_view::npos)
                            throw std::invalid_argument("Unterminated array object type in descriptor");
                        i = semicolon + 1;
                    } else {
                        i++;
                    }
                    arguments += 2;

                    break;
                }

                default:
                    throw std::invalid_argument(std::string("Unexpected character in descriptor: ") + c);
            }
        }

        return arguments;
    }

    void CallInsnNode::print(std::ostream& stream) const {
        stream << std::format("{} Function {}:{}:{}", mOpcode.name, mModule, mName, mDescriptor);
    }

    void CallInsnNode::emit(moduleweb::InsnList& list) {
        list.callInsn(mOpcode.opcode, mModule, mName, mDescriptor);
    }
}