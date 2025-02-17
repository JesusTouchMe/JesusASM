// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/CallInsnNode.h"

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

    i32 CallInsnNode::getStackPushes() const {
        auto pos = mDescriptor.rfind(')');
        if (pos == std::string_view::npos) {
            throw std::runtime_error("Bad descriptor");
        }
    }

    i32 CallInsnNode::getStackPops() const {
        i32 arguments = 0;
        bool parsing_ref = false;

        for (char c : mDescriptor) {
            if (c == ')') {
                break;
            }

            if (parsing_ref) {
                if (c == ';') {
                    parsing_ref = false;
                    arguments += 2; // 2 values because 64 bits
                }
                continue;
            }

            if (c == 'R') {
                parsing_ref = true;
                continue;
            }

            if (c == 'L' || c == 'D' || c == 'H') {
                arguments += 2;
            } else {
                arguments += 1;
            }
        }

        return arguments;
    }

    void CallInsnNode::emit(moduleweb::InsnList& list) {
        list.callInsn(mOpcode, mModule, mName, mDescriptor);
    }
}