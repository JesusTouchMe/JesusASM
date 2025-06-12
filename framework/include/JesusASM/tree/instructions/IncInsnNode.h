// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_INCINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_INCINSNNODE_H 1

#include "JesusASM/tree/AbstractInsnNode.h"

namespace JesusASM::tree {
    class IncInsnNode : public AbstractInsnNode {
    public:
        IncInsnNode(Opcode opcode, u16 index, i16 increment);

        void print(std::ostream& stream) const override;

        void emit(moduleweb::InsnList& list) override;

    private:
        u16 mIndex;
        i16 mIncrement;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_INCINSNNODE_H