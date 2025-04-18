// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_VARINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_VARINSNNODE_H

#include "JesusASM/tree/AbstractInsnNode.h"

namespace JesusASM::tree {
    class VarInsnNode : public AbstractInsnNode {
    public:
        VarInsnNode(Opcode opcode, u16 index);

        void emit(moduleweb::InsnList& list) override;

    private:
        u16 mIndex;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_VARINSNNODE_H
