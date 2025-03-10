// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/IntInsnNode.h"

namespace JesusASM::tree {
    IntInsnNode::IntInsnNode(Opcode opcode, OperandSize size, i64 value)
        : AbstractInsnNode(InsnType::INT, opcode)
        , mSize(size)
        , mValue(value) {}

    i32 IntInsnNode::getStackPushes() const {
        if (mOpcode == Opcodes::NEWARRAY) {
            return 2;
        }

        if (mSize == OperandSize::LONG) return 2;
        else return 1;
    }

    i32 IntInsnNode::getStackPops() const {
        if (mOpcode == Opcodes::NEWARRAY) {
            return 1;
        }

        return 0;
    }

    void IntInsnNode::emit(moduleweb::InsnList& list) {
        switch (mSize) {
            case OperandSize::BYTE:
                list.byteInsn(mOpcode, static_cast<i8>(mValue));
                break;
            case OperandSize::SHORT:
                list.shortInsn(mOpcode, static_cast<i16>(mValue));
                break;
            case OperandSize::INT:
                list.intInsn(mOpcode, static_cast<i32>(mValue));
                break;
            case OperandSize::LONG:
                list.longInsn(mOpcode, mValue);
                break;
        }
    }
}