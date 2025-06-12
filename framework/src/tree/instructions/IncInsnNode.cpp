// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/IncInsnNode.h"

#include <format>

namespace JesusASM::tree {
    IncInsnNode::IncInsnNode(Opcode opcode, u16 index, i16 increment)
        : AbstractInsnNode(InsnType::INC, opcode)
        , mIndex(index)
        , mIncrement(increment) {}

    void IncInsnNode::print(std::ostream& stream) const {
        stream << std::format("{} #{}, {}", mOpcode.name, mIndex, mIncrement);
    }

    void IncInsnNode::emit(moduleweb::InsnList& list) {
        list.setLocalIndex(mIndex);
        if (mOpcode.opcode == Opcode::LINC) list.setLocalIndex(mIndex + 1);

        list.incInsn(mOpcode.opcode, mIndex, mIncrement);
    }
}
