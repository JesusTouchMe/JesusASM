// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/MethodInsnNode.h"

#include <format>

namespace JesusASM::tree {
    MethodInsnNode::MethodInsnNode(Opcode opcode, std::string ownerModule, std::string owner, std::string name, std::string descriptor)
        : AbstractInsnNode(InsnType::METHOD, opcode)
        , mOwnerModule(std::move(ownerModule))
        , mOwner(std::move(owner))
        , mName(std::move(name))
        , mDescriptor(std::move(descriptor)) {}

    int MethodInsnNode::getStackPushes() const {
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
            case 'F':
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

    int MethodInsnNode::getStackPops() const {
        if (mDescriptor.front() != '(') {
            throw std::runtime_error("bad descriptor");
        }

        int arguments = 2; // a method descriptor doesn't have the 'this' argument unlkie the function it points to

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

    void MethodInsnNode::print(std::ostream& stream) const {
        stream << std::format("{} Method {}:{}:{}:{}", mOpcode.name, mOwnerModule, mOwner, mName, mDescriptor);
    }

    void MethodInsnNode::emit(moduleweb::InsnList& list) {
        list.methodInsn(mOpcode.opcode, mOwnerModule, mOwner, mName, mDescriptor);
    }
}
