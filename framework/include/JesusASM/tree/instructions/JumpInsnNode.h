// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_JUMPINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_JUMPINSNNODE_H

#include "JesusASM/tree/instructions/LabelNode.h"

namespace JesusASM::tree {
    class JumpInsnNode : public AbstractInsnNode {
    friend class InsnList;
    public:
        JumpInsnNode(Opcode opcode, LabelNode* label);

        i32 getStackPops() const override;

        void emit(moduleweb::InsnList& list) override;
        void preEmit(moduleweb::InsnList& list) override;

    private:
        LabelNode* mDestination;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_JUMPINSNNODE_H
