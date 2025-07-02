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
            EnumOpcodesMember(Opcodes::AND, "and", 1, 2),
            EnumOpcodesMember(Opcodes::OR, "or", 1, 2),
            EnumOpcodesMember(Opcodes::XOR, "xor", 1, 2),
            EnumOpcodesMember(Opcodes::SHL, "shl", 1, 2),
            EnumOpcodesMember(Opcodes::SHR, "shr", 1, 2),
            EnumOpcodesMember(Opcodes::NOT, "not", 1, 1),
            EnumOpcodesMember(Opcodes::NEG, "neg", 1, 1),
            EnumOpcodesMember(Opcodes::POP, "pop", 0, 1),
            EnumOpcodesMember(Opcodes::DUP, "dup", 2, 1),
            EnumOpcodesMember(Opcodes::DUP2, "dup2", 4, 2),
            EnumOpcodesMember(Opcodes::DUP_X1, "dup_x1", 3, 2),
            EnumOpcodesMember(Opcodes::DUP_X2, "dup_x2", 4, 3),
            EnumOpcodesMember(Opcodes::SWAP, "swap", 2, 2),
            EnumOpcodesMember(Opcodes::INC, "inc", 0, 0),
            EnumOpcodesMember(Opcodes::LOAD, "load", 1, 0),
            EnumOpcodesMember(Opcodes::STORE, "store", 0, 1),
            EnumOpcodesMember(Opcodes::HLOAD, "hload", 1, 0),
            EnumOpcodesMember(Opcodes::HSTORE, "hstore", 0, 1),
            EnumOpcodesMember(Opcodes::RLOAD, "rload", 1, 0),
            EnumOpcodesMember(Opcodes::RSTORE, "rstore", 0, 1),
            EnumOpcodesMember(Opcodes::RLOAD_0, "rload_0", 1, 0),
            EnumOpcodesMember(Opcodes::BALOAD, "baload", 1, 2),
            EnumOpcodesMember(Opcodes::BASTORE, "bastore", 0, 3),
            EnumOpcodesMember(Opcodes::CALOAD, "caload", 1, 2),
            EnumOpcodesMember(Opcodes::CASTORE, "castore", 0, 3),
            EnumOpcodesMember(Opcodes::SALOAD, "saload", 1, 2),
            EnumOpcodesMember(Opcodes::SASTORE, "sastore", 0, 3),
            EnumOpcodesMember(Opcodes::IALOAD, "iaload", 1, 2),
            EnumOpcodesMember(Opcodes::IASTORE, "iastore", 0, 3),
            EnumOpcodesMember(Opcodes::LALOAD, "laload", 2, 2),
            EnumOpcodesMember(Opcodes::LASTORE, "lastore", 0, 3),
            EnumOpcodesMember(Opcodes::HALOAD, "haload", 2, 2),
            EnumOpcodesMember(Opcodes::HASTORE, "hastore", 0, 3),
            EnumOpcodesMember(Opcodes::RALOAD, "raload", 2, 2),
            EnumOpcodesMember(Opcodes::RASTORE, "rastore", 0, 3),
            EnumOpcodesMember(Opcodes::ARRAYLENGTH, "arraylength", 1, 1),
            EnumOpcodesMember(Opcodes::NEW, "new", 1, 0),
            EnumOpcodesMember(Opcodes::NEWARRAY, "newarray", 1, 1),
            EnumOpcodesMember(Opcodes::RNEWARRAY, "rnewarray", 1, 1),
            EnumOpcodesMember(Opcodes::ISINSTANCE, "isinstance", 1, 2),
            EnumOpcodesMember(Opcodes::GETFIELD, "getfield", 1, 1),
            EnumOpcodesMember(Opcodes::SETFIELD, "setfield", 0, 2),
            EnumOpcodesMember(Opcodes::GETGLOBAL, "getglobal", 1, 0),
            EnumOpcodesMember(Opcodes::SETGLOBAL, "setglobal", 0, 1),
            EnumOpcodesMember(Opcodes::JMP_CMPEQ, "jmp_cmpeq", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_CMPNE, "jmp_cmpne", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_CMPLT, "jmp_cmplt", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_CMPGT, "jmp_cmpgt", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_CMPLE, "jmp_cmple", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_CMPGE, "jmp_cmpge", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_HCMPEQ, "jmp_hcmpeq", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_HCMPNE, "jmp_hcmpne", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_RCMPEQ, "jmp_rcmpeq", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_RCMPNE, "jmp_rcmpne", 0, 2),
            EnumOpcodesMember(Opcodes::JMP_HNULL, "jmp_hnull", 0, 1),
            EnumOpcodesMember(Opcodes::JMP_HNONNULL, "jmp_hnonnull", 0, 1),
            EnumOpcodesMember(Opcodes::JMP_RNULL, "jmp_rnull", 0, 1),
            EnumOpcodesMember(Opcodes::JMP_RNONNULL, "jmp_rnonnull", 0, 1),
            EnumOpcodesMember(Opcodes::JMPEQ, "jmpeq", 0, 1),
            EnumOpcodesMember(Opcodes::JMPNE, "jmpne", 0, 1),
            EnumOpcodesMember(Opcodes::JMPLT, "jmplt", 0, 1),
            EnumOpcodesMember(Opcodes::JMPGT, "jmpgt", 0, 1),
            EnumOpcodesMember(Opcodes::JMPLE, "jmple", 0, 1),
            EnumOpcodesMember(Opcodes::JMPGE, "jmpge", 0, 1),
            EnumOpcodesMember(Opcodes::JMP, "jmp", 0, 0),
            EnumOpcodesMember(Opcodes::CMP, "cmp", 1, 2),
            EnumOpcodesMember(Opcodes::HCMP, "hcmp", 1, 2),
            EnumOpcodesMember(Opcodes::RCMP, "rcmp", 1, 2),
            EnumOpcodesMember(Opcodes::BPUSH, "bpush", 1, 0),
            EnumOpcodesMember(Opcodes::SPUSH, "spush", 1, 0),
            EnumOpcodesMember(Opcodes::IPUSH, "ipush", 1, 0),
            EnumOpcodesMember(Opcodes::LPUSH, "lpush", 1, 0),
            EnumOpcodesMember(Opcodes::L2B, "l2b", 1, 1),
            EnumOpcodesMember(Opcodes::L2S, "l2s", 1, 1),
            EnumOpcodesMember(Opcodes::L2I, "l2i", 1, 1),
            EnumOpcodesMember(Opcodes::CONST_M1, "const_m1", 1, 0),
            EnumOpcodesMember(Opcodes::CONST_0, "const_0", 1, 0),
            EnumOpcodesMember(Opcodes::CONST_1, "const_1", 1, 0),
            EnumOpcodesMember(Opcodes::CONST_2, "const_2", 1, 0),
            EnumOpcodesMember(Opcodes::CONST_3, "const_3", 1, 0),
            EnumOpcodesMember(Opcodes::CONST_4, "const_4", 1, 0),
            EnumOpcodesMember(Opcodes::HCONST_NULL, "hconst_null", 1, 0),
            EnumOpcodesMember(Opcodes::RCONST_NULL, "rconst_null", 1, 0),
            EnumOpcodesMember(Opcodes::CALL, "call", 0, 0), // push/pop implemented by CallInsnNode
            EnumOpcodesMember(Opcodes::CALLVIRTUAL, "callvirtual", 0, 0), // push/pop implemented by MethodInsnNode
            EnumOpcodesMember(Opcodes::RETURN, "return", 0, 0),
            EnumOpcodesMember(Opcodes::LRETURN, "lreturn", 0, 1),
            EnumOpcodesMember(Opcodes::HRETURN, "hreturn", 0, 1),
            EnumOpcodesMember(Opcodes::RRETURN, "rreturn", 0, 1),
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