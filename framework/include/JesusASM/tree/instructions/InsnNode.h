// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_INSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_INSNNODE_H

#include "JesusASM/tree/AbstractInsnNode.h"

namespace JesusASM::tree {
    class InsnNode : public AbstractInsnNode {
    public:
        InsnNode(Opcode opcode);

        i32 getStackPushes() const override;

        i32 getStackPops() const override;

        void emit(moduleweb::InsnList& list) override;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_INSNNODE_H
