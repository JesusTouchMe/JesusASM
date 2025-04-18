// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/JumpInsnNode.h"

#include <iostream>

namespace JesusASM::tree {

    JumpInsnNode::JumpInsnNode(Opcode opcode, LabelNode* label)
        : AbstractInsnNode(InsnType::JUMP, opcode)
        , mDestination(label) {}

    void JumpInsnNode::emit(moduleweb::InsnList& list) {
        list.jumpInsn(mOpcode.opcode, mDestination->getLabel(list));
    }

    void JumpInsnNode::preEmit(moduleweb::InsnList& list) {
        if (mLabel != nullptr) {
            mLabel->addSuccessor(mDestination);
            mDestination->addPredecessor(mLabel);
        }
    }
}