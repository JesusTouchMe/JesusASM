// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/JumpInsnNode.h"

#include <iostream>

namespace JesusASM::tree {

    JumpInsnNode::JumpInsnNode(Opcode opcode, LabelNode* label)
        : AbstractInsnNode(InsnType::JUMP, opcode)
        , mDestination(label) {}

    i32 JumpInsnNode::getStackPops() const {
        switch (mOpcode) {
            case Opcodes::JMP_ICMPEQ:
            case Opcodes::JMP_ICMPNE:
            case Opcodes::JMP_ICMPLT:
            case Opcodes::JMP_ICMPGT:
            case Opcodes::JMP_ICMPLE:
            case Opcodes::JMP_ICMPGE:
                return 2;

            case Opcodes::JMPEQ:
            case Opcodes::JMPNE:
            case Opcodes::JMPLT:
            case Opcodes::JMPGT:
            case Opcodes::JMPLE:
            case Opcodes::JMPGE:
                return 1;

            case Opcodes::JMP:
                return 0;
        }

        std::cout << "warning: weird opcode in jump (" << mOpcode << ")\n";

        return 0;
    }

    void JumpInsnNode::emit(moduleweb::InsnList& list) {
        list.jumpInsn(mOpcode, mDestination->getLabel(list));
    }

    void JumpInsnNode::preEmit(moduleweb::InsnList& list) {
        if (mLabel != nullptr) {
            mLabel->addSuccessor(mDestination);
            mDestination->addPredecessor(mLabel);
        }
    }
}