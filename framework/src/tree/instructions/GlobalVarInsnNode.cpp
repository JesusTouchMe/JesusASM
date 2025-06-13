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

    void GlobalVarInsnNode::print(std::ostream& stream) const {
        stream << std::format("{} Global {}:{}:{}", mOpcode.name, mModule, mName, mDescriptor);
    }

    void GlobalVarInsnNode::emit(moduleweb::InsnList& list) {
        list.globalVarInsn(mOpcode.opcode, mModule, mName, mDescriptor);
    }
}