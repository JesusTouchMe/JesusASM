// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/InsnNode.h"

namespace JesusASM::tree {
    InsnNode::InsnNode(Opcode opcode)
        : AbstractInsnNode(InsnType::INSN, opcode) {}

    i32 InsnNode::getStackPushes() const { // assumes only proper instructions are passed
        switch (mOpcode) {
            case Opcodes::ADD:
            case Opcodes::SUB:
            case Opcodes::MUL:
            case Opcodes::DIV:
            case Opcodes::REM:
            case Opcodes::AND:
            case Opcodes::OR:
            case Opcodes::XOR:
            case Opcodes::NOT:
            case Opcodes::NEG:
            case Opcodes::ICMP:
            case Opcodes::LCMP:
            case Opcodes::CONST_M1:
            case Opcodes::CONST_0:
            case Opcodes::CONST_1:
                return 1;

            case Opcodes::LADD:
            case Opcodes::LSUB:
            case Opcodes::LMUL:
            case Opcodes::LDIV:
            case Opcodes::LREM:
            case Opcodes::LAND:
            case Opcodes::LOR:
            case Opcodes::LXOR:
            case Opcodes::LNOT:
            case Opcodes::LNEG:
            case Opcodes::LPUSH:
            case Opcodes::LCONST_0:
            case Opcodes::LCONST_1:
                return 2;
        }

        return 0;
    }

    i32 InsnNode::getStackPops() const {
        switch (mOpcode) {
            case Opcodes::NOT:
            case Opcodes::NEG:
            case Opcodes::JMPEQ:
            case Opcodes::JMPNE:
            case Opcodes::JMPLT:
            case Opcodes::JMPGT:
            case Opcodes::JMPLE:
            case Opcodes::JMPGE:
            case Opcodes::IRETURN:
                return 1;

            case Opcodes::ADD:
            case Opcodes::SUB:
            case Opcodes::MUL:
            case Opcodes::DIV:
            case Opcodes::REM:
            case Opcodes::AND:
            case Opcodes::OR:
            case Opcodes::XOR:
            case Opcodes::LNOT:
            case Opcodes::LNEG:
            case Opcodes::JMP_ICMPEQ:
            case Opcodes::JMP_ICMPNE:
            case Opcodes::JMP_ICMPLT:
            case Opcodes::JMP_ICMPGT:
            case Opcodes::JMP_ICMPLE:
            case Opcodes::JMP_ICMPGE:
            case Opcodes::ICMP:
            case Opcodes::LRETURN:
                return 2;

            case Opcodes::LADD:
            case Opcodes::LSUB:
            case Opcodes::LMUL:
            case Opcodes::LDIV:
            case Opcodes::LREM:
            case Opcodes::LAND:
            case Opcodes::LOR:
            case Opcodes::LXOR:
            case Opcodes::LCMP:
                return 4;
        }

        return 0;
    }

    void InsnNode::emit(moduleweb::InsnList& list) {
        list.insn(mOpcode);
    }
}