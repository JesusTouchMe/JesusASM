// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/GlobalVarInsnNode.h"

#include <format>

namespace JesusASM::tree {
    GlobalVarInsnNode::GlobalVarInsnNode(Opcode opcode, std::string_view module, std::string_view name, std::string_view descriptor)
        : AbstractInsnNode(InsnType::GLOBAL, opcode)
        , mModule(module)
        , mName(name)
        , mDescriptor(descriptor) {}

    GlobalVarInsnNode::GlobalVarInsnNode(Opcode opcode, std::string&& module, std::string&& name, std::string&& descriptor)
        : AbstractInsnNode(InsnType::GLOBAL, opcode)
        , mModule(std::move(module))
        , mName(std::move(name))
        , mDescriptor(std::move(descriptor)) {}

    int GlobalVarInsnNode::getStackPushes() const {
        if (mOpcode.opcode == Opcodes::GETGLOBAL) {
            char c = mDescriptor[0];
            switch (c) {
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

        return 0;
    }

    int GlobalVarInsnNode::getStackPops() const {
        if (mOpcode.opcode == Opcodes::SETGLOBAL) {
            char c = mDescriptor[0];
            switch (c) {
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

        return 0;
    }

    void GlobalVarInsnNode::print(std::ostream& stream) const {
        stream << std::format("{} Global {}:{}:{}", mOpcode.name, mModule, mName, mDescriptor);
    }

    void GlobalVarInsnNode::emit(moduleweb::InsnList& list) {
        list.globalVarInsn(mOpcode.opcode, mModule, mName, mDescriptor);
    }
}