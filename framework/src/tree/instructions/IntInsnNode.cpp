// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/IntInsnNode.h"

#include <format>

namespace JesusASM::tree {
    static std::string_view GetOperandSizeString(OperandSize size) {
        switch (size) {
            case OperandSize::BYTE:
                return "BYTE";
            case OperandSize::SHORT:
                return "SHORT";
            case OperandSize::INT:
                return "INT";
            case OperandSize::LONG:
                return "LONG";
        }
    }

    IntInsnNode::IntInsnNode(Opcode opcode, OperandSize size, i64 value)
        : AbstractInsnNode(InsnType::INT, opcode)
        , mSize(size)
        , mValue(value) {}

    void IntInsnNode::print(std::ostream& stream) const {
        stream << std::format("{} {} {}", mOpcode.name, GetOperandSizeString(mSize), mValue);
    }

    void IntInsnNode::emit(moduleweb::InsnList& list) {
        switch (mSize) {
            case OperandSize::BYTE:
                list.byteInsn(mOpcode.opcode, static_cast<i8>(mValue));
                break;
            case OperandSize::SHORT:
                list.shortInsn(mOpcode.opcode, static_cast<i16>(mValue));
                break;
            case OperandSize::INT:
                list.intInsn(mOpcode.opcode, static_cast<i32>(mValue));
                break;
            case OperandSize::LONG:
                list.longInsn(mOpcode.opcode, mValue);
                break;
        }
    }
}