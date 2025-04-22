// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_INTINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_INTINSNNODE_H

#include "JesusASM/tree/AbstractInsnNode.h"

#include <string>

namespace JesusASM::tree {
    enum class OperandSize {
        BYTE,
        SHORT,
        INT,
        LONG
    };

    class IntInsnNode : public AbstractInsnNode {
    public:
        IntInsnNode(Opcode opcode, OperandSize size, i64 value);

        void print(std::ostream& stream) const override;

        void emit(moduleweb::InsnList& list) override;

    private:
        OperandSize mSize;
        i64 mValue;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_INTINSNNODE_H
