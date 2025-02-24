// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/VarInsnNode.h"

namespace JesusASM::tree {
    VarInsnNode::VarInsnNode(Opcode opcode, u16 index)
        : AbstractInsnNode(InsnType::VAR, opcode)
        , mIndex(index) {}

    i32 VarInsnNode::getStackPushes() const {
        switch (mOpcode) {
            case Opcodes::ILOAD:
                return 1;
            case Opcodes::LLOAD:
            case Opcodes::HLOAD:
            case Opcodes::RLOAD:
                return 2;
        }

        return 0;
    }

    i32 VarInsnNode::getStackPops() const {
        switch (mOpcode) {
            case Opcodes::ISTORE:
                return 1;
            case Opcodes::LSTORE:
            case Opcodes::HSTORE:
            case Opcodes::RSTORE:
                return 2;
        }

        return 0;
    }

    void VarInsnNode::emit(moduleweb::InsnList& list) {
        list.setLocalIndex(mIndex);

        switch (mOpcode) {
            case Opcodes::LSTORE:
            case Opcodes::HSTORE:
            case Opcodes::RSTORE:
                list.setLocalIndex(mIndex + 1);
                break;
        }

        list.varInsn(mOpcode, mIndex);
    }
}