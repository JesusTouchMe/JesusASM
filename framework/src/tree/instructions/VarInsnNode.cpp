// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/VarInsnNode.h"

namespace JesusASM::tree {
    VarInsnNode::VarInsnNode(Opcode opcode, u16 index)
        : AbstractInsnNode(InsnType::VAR, opcode)
        , mIndex(index) {}

    void VarInsnNode::emit(moduleweb::InsnList& list) {
        list.setLocalIndex(mIndex);

        switch (mOpcode.opcode) {
            case Opcodes::LLOAD:
            case Opcodes::HLOAD:
            case Opcodes::RLOAD:
            case Opcodes::LSTORE:
            case Opcodes::HSTORE:
            case Opcodes::RSTORE:
                list.setLocalIndex(mIndex + 1);
                break;
        }

        list.varInsn(mOpcode.opcode, mIndex);
    }
}