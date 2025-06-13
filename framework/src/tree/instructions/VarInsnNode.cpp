// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/VarInsnNode.h"

#include <format>

namespace JesusASM::tree {
    VarInsnNode::VarInsnNode(Opcode opcode, u16 index)
        : AbstractInsnNode(InsnType::VAR, opcode)
        , mIndex(index) {}

    void VarInsnNode::print(std::ostream& stream) const {
        stream << std::format("{} #{}", mOpcode.name, mIndex);
    }

    void VarInsnNode::emit(moduleweb::InsnList& list) {
        list.setLocalIndex(mIndex);
        list.varInsn(mOpcode.opcode, mIndex);
    }
}