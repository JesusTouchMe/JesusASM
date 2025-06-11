// Copyright 2025 JesusTouchMe

#include "JesusASM/Opcodes.h"

#include <algorithm>
#include <array>
#include <stdexcept>

namespace JesusASM::EnumOpcodes {
    std::array members {
            EnumOpcodesMember(Opcodes::NOP, "nop", 0, 0),
            EnumOpcodesMember(Opcodes::ADD, "add", 1, 2),
            EnumOpcodesMember(Opcodes::SUB, "sub", 1, 2),
            EnumOpcodesMember(Opcodes::MUL, "mul", 1, 2),
            EnumOpcodesMember(Opcodes::DIV, "div", 1, 2),
            EnumOpcodesMember(Opcodes::REM, "rem", 1, 2),
            EnumOpcodesMember(Opcodes::LADD, "ladd", 2, 4),
            EnumOpcodesMember(Opcodes::LSUB, "lsub", 2, 4),
            EnumOpcodesMember(Opcodes::LMUL, "lmul", 2, 4),
            EnumOpcodesMember(Opcodes::LDIV, "ldiv", 2, 4),
            EnumOpcodesMember(Opcodes::LREM, "lrem", 2, 4),
            EnumOpcodesMember(Opcodes::AND, "and", 1, 2),
            EnumOpcodesMember(Opcodes::OR, "or", 1, 2),
            EnumOpcodesMember(Opcodes::XOR, "xor", 1, 2),
            EnumOpcodesMember(Opcodes::SHL, "shl", 1, 2),
            EnumOpcodesMember(Opcodes::SHR, "shr", 1, 2),
            EnumOpcodesMember(Opcodes::LAND, "land", 2, 4),
            EnumOpcodesMember(Opcodes::LOR, "lor", 2, 4),
            EnumOpcodesMember(Opcodes::LXOR, "lxor", 2, 4),
            EnumOpcodesMember(Opcodes::LSHL, "lshl", 2, 4),
            EnumOpcodesMember(Opcodes::LSHR, "lshr", 2, 4),
            EnumOpcodesMember(Opcodes::NOT, "not", 1, 1),
            EnumOpcodesMember(Opcodes::NEG, "neg", 1, 1),
            EnumOpcodesMember(Opcodes::LNOT, "lnot", 2, 2),
            EnumOpcodesMember(Opcodes::LNEG, "lneg", 2, 2),
            EnumOpcodesMember(Opcodes::POP, "pop", 0, 1),
            EnumOpcodesMember(Opcodes::POP2, "pop2", 0, 2),
            EnumOpcodesMember(Opcodes::DUP, "dup", 2, 1),
            EnumOpcodesMember(Opcodes::DUP2, "dup2", 4, 2),
            EnumOpcodesMember(Opcodes::SWAP, "swap", 2, 2),
            EnumOpcodesMember(Opcodes::SWAP2, "swap2", 4, 4),
            EnumOpcodesMember(Opcodes::ILOAD, "iload", 1, 0),
            EnumOpcodesMember(Opcodes::ISTORE, "istore", 0, 1),
            EnumOpcodesMember(Opcodes::LLOAD, "lload", 2, 0),
            EnumOpcodesMember(Opcodes::LSTORE, "lstore", 0, 2),
            EnumOpcodesMember(Opcodes::HLOAD, "hload", 2, 0),
            EnumOpcodesMember(Opcodes::HSTORE, "hstore", 0, 2),
            EnumOpcodesMember(Opcodes::RLOAD, "rload", 2, 0),
            EnumOpcodesMember(Opcodes::RSTORE, "rstore", 0, 2),
            EnumOpcodesMember(Opcodes::RLOAD_0, "rload_0", 2, 0),
            EnumOpcodesMember(Opcodes::BALOAD, "baload", 1, 3),
            EnumOpcodesMember(Opcodes::BASTORE, "bastore", 0, 4),
            EnumOpcodesMember(Opcodes::CALOAD, "caload", 1, 3),
            EnumOpcodesMember(Opcodes::CASTORE, "castore", 0, 4),
            EnumOpcodesMember(Opcodes::SALOAD, "saload", 1, 3),
            EnumOpcodesMember(Opcodes::SASTORE, "sastore", 0, 4),
            EnumOpcodesMember(Opcodes::IALOAD, "iaload", 1, 3),
            EnumOpcodesMember(Opcodes::IASTORE, "iastore", 0, 4),
            EnumOpcodesMember(Opcodes::LALOAD, "laload", 2, 3),
            EnumOpcodesMember(Opcodes::LASTORE, "lastore", 0, 5),
            EnumOpcodesMember(Opcodes::HALOAD, "haload", 2, 3),
            EnumOpcodesMember(Opcodes::HASTORE, "hastore", 0, 5),
            EnumOpcodesMember(Opcodes::RALOAD, "raload", 2, 3),
            EnumOpcodesMember(Opcodes::RASTORE, "rastore", 0, 5),
            EnumOpcodesMember(Opcodes::ARRAYLENGTH, "arraylength", 1, 2),
            EnumOpcodesMember(Opcodes::NEW, "new", 2, 0),
            EnumOpcodesMember(Opcodes::NEWARRAY, "newarray", 2, 1),
            EnumOpcodesMember(Opcodes::RNEWARRAY, "rnewarray", 2, 1),
            EnumOpcodesMember(Opcodes::ISINSTANCE, "isinstance", 1, 2),
            EnumOpcodesMember(Opcodes::GETFIELD, "getfield", 0, 0), // push/pop implemented by FieldInsnNode
            EnumOpcodesMember(Opcodes::SETFIELD, "setfield", 0, 0), // push/pop implemented by FieldInsnNode
            EnumOpcodesMember(Opcodes::GETGLOBAL, "getglobal", 0, 0), // push/pop implemented by GlobalVarInsnNode
            EnumOpcodesMember(Opcodes::SETGLOBAL, "setglobal", 0, 0), // push/pop implemented by GlobalVarInsnNode
            EnumOpcodesMember(Opcodes::JMP_ICMPEQ, "jmp_icmpeq", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_ICMPNE, "jmp_icmpne", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_ICMPLT, "jmp_icmplt", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_ICMPGT, "jmp_icmpgt", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_ICMPLE, "jmp_icmple", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_ICMPGE, "jmp_icmpge", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_HCMPEQ, "jmp_hcmpeq", 0, 4),
            EnumOpcodesMember(Opcodes::JMP_HCMPNE, "jmp_hcmpne", 0, 4),
            EnumOpcodesMember(Opcodes::JMP_RCMPEQ, "jmp_rcmpeq", 0, 4),
            EnumOpcodesMember(Opcodes::JMP_RCMPNE, "jmp_rcmpne", 0, 4),
            EnumOpcodesMember(Opcodes::JMP_HNULL, "jmp_hnull", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_HNONNULL, "jmp_hnonnull", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_RNULL, "jmp_rnull", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_RNONNULL, "jmp_rnonnull", 0, 2),
            EnumOpcodesMember(Opcodes::JMPEQ, "jmpeq", 0, 1),
            EnumOpcodesMember(Opcodes::JMPNE, "jmpne", 0, 1),
            EnumOpcodesMember(Opcodes::JMPLT, "jmplt", 0, 1),
            EnumOpcodesMember(Opcodes::JMPGT, "jmpgt", 0, 1),
            EnumOpcodesMember(Opcodes::JMPLE, "jmple", 0, 1),
            EnumOpcodesMember(Opcodes::JMPGE, "jmpge", 0, 1),
            EnumOpcodesMember(Opcodes::JMP, "jmp", 0, 0),
            EnumOpcodesMember(Opcodes::ICMP, "icmp", 1, 2),
            EnumOpcodesMember(Opcodes::LCMP, "lcmp", 1, 4),
            EnumOpcodesMember(Opcodes::HCMP, "hcmp", 1, 4),
            EnumOpcodesMember(Opcodes::RCMP, "rcmp", 1, 4),
            EnumOpcodesMember(Opcodes::BPUSH, "bpush", 1, 0),
            EnumOpcodesMember(Opcodes::SPUSH, "spush", 1, 0),
            EnumOpcodesMember(Opcodes::IPUSH, "ipush", 1, 0),
            EnumOpcodesMember(Opcodes::LPUSH, "lpush", 2, 0),
            EnumOpcodesMember(Opcodes::I2B, "i2b", 1, 1),
            EnumOpcodesMember(Opcodes::I2S, "i2s", 1, 1),
            EnumOpcodesMember(Opcodes::I2L, "i2l", 2, 1),
            EnumOpcodesMember(Opcodes::L2I, "l2i", 1, 2),
            EnumOpcodesMember(Opcodes::CONST_M1, "const_m1", 1, 0),
            EnumOpcodesMember(Opcodes::CONST_0, "const_0", 1, 0),
            EnumOpcodesMember(Opcodes::CONST_1, "const_1", 1, 0),
            EnumOpcodesMember(Opcodes::LCONST_0, "lconst_0", 2, 0),
            EnumOpcodesMember(Opcodes::LCONST_1, "lconst_1", 2, 0),
            EnumOpcodesMember(Opcodes::HCONST_NULL, "hconst_null", 2, 0),
            EnumOpcodesMember(Opcodes::RCONST_NULL, "rconst_null", 2, 0),
            EnumOpcodesMember(Opcodes::CALL, "call", 0, 0), // push/pop implemented by CallInsnNode
            EnumOpcodesMember(Opcodes::CALLVIRTUAL, "callvirtual", 0, 0), // push/pop implemented by MethodInsnNode
            EnumOpcodesMember(Opcodes::RETURN, "return", 0, 0),
            EnumOpcodesMember(Opcodes::IRETURN, "ireturn", 0, 1),
            EnumOpcodesMember(Opcodes::LRETURN, "lreturn", 0, 2),
            EnumOpcodesMember(Opcodes::HRETURN, "hreturn", 0, 2),
            EnumOpcodesMember(Opcodes::RRETURN, "rreturn", 0, 2),
            EnumOpcodesMember(Opcodes::LDC, "ldc", 0, 0), // push/pop implemented by LdcInsnNode
    };

    const EnumOpcodesMember& Get(Opcode opcode) {
        auto it = std::find_if(members.begin(), members.end(), [opcode](const EnumOpcodesMember& member) {
            return member.opcode == opcode;
        });

        if (it == members.end()) {
            throw std::runtime_error("bad enum member access (opcode)");
        }

        return *it;
    }

    const EnumOpcodesMember& Get(std::string_view name) {
        auto it = std::find_if(members.begin(), members.end(), [name](const EnumOpcodesMember& member) {
            return member.name == name;
        });

        if (it == members.end()) {
            throw std::runtime_error("bad enum member access (name)");
        }

        return *it;
    }
}