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
            case Opcodes::SHL:
            case Opcodes::SHR:
            case Opcodes::NOT:
            case Opcodes::NEG:
            case Opcodes::DUP:
            case Opcodes::BALOAD:
            case Opcodes::CALOAD:
            case Opcodes::SALOAD:
            case Opcodes::IALOAD:
            case Opcodes::ARRAYLENGTH:
            case Opcodes::ICMP:
            case Opcodes::LCMP:
            case Opcodes::HCMP:
            case Opcodes::RCMP:
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
            case Opcodes::LSHL:
            case Opcodes::LSHR:
            case Opcodes::LNOT:
            case Opcodes::LNEG:
            case Opcodes::DUP2:
            case Opcodes::RLOAD_0:
            case Opcodes::LALOAD:
            case Opcodes::HALOAD:
            case Opcodes::RALOAD:
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
            case Opcodes::SHL:
            case Opcodes::SHR:
            case Opcodes::LNOT:
            case Opcodes::LNEG:
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
            case Opcodes::LSHL:
            case Opcodes::LSHR:
            case Opcodes::LCMP:
            case Opcodes::HCMP:
            case Opcodes::RCMP:
                return 4;

            case Opcodes::BALOAD:
            case Opcodes::CALOAD:
            case Opcodes::SALOAD:
            case Opcodes::IALOAD:
            case Opcodes::LALOAD:
            case Opcodes::HALOAD:
            case Opcodes::RALOAD:
                return 3;

            case Opcodes::BASTORE:
            case Opcodes::CASTORE:
            case Opcodes::SASTORE:
            case Opcodes::IASTORE:
                return 4;
            case Opcodes::LASTORE:
            case Opcodes::HASTORE:
            case Opcodes::RASTORE:
                return 5;
        }

        return 0;
    }

    void InsnNode::emit(moduleweb::InsnList& list) {
        if (mOpcode == Opcodes::RLOAD_0) {
            list.setLocalIndex(1); // 0 and 1 at the same time
        }

        list.insn(mOpcode);
    }
}