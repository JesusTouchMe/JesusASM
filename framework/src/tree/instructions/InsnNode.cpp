// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/InsnNode.h"

namespace JesusASM::tree {
    InsnNode::InsnNode(Opcode opcode)
        : AbstractInsnNode(InsnType::INSN, opcode) {}

    void InsnNode::print(std::ostream& stream) const {
        stream << mOpcode.name;
    }

    void InsnNode::emit(moduleweb::InsnList& list) {
        if (mOpcode.opcode == Opcodes::RLOAD_0) {
            list.setLocalIndex(0); // 0 and 1 at the same time
        }

        list.insn(mOpcode.opcode);
    }
}