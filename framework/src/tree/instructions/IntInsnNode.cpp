// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/IntInsnNode.h"

namespace JesusASM::tree {
    IntInsnNode::IntInsnNode(Opcode opcode, OperandSize size, i64 value)
        : AbstractInsnNode(InsnType::INT, opcode)
        , mSize(size)
        , mValue(value) {}

    IntInsnNode::IntInsnNode(Opcode opcode, OperandSize size, u64 value)
        : IntInsnNode(opcode, size, static_cast<i64>(value)) {}

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