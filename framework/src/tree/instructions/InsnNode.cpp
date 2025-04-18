// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/InsnNode.h"

namespace JesusASM::tree {
    InsnNode::InsnNode(Opcode opcode)
        : AbstractInsnNode(InsnType::INSN, opcode) {}

    void InsnNode::emit(moduleweb::InsnList& list) {
        if (mOpcode.opcode == Opcodes::RLOAD_0) {
            list.setLocalIndex(1); // 0 and 1 at the same time
        }

        list.insn(mOpcode.opcode);
    }
}