// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_OPCODES_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_OPCODES_H 1

#include <string>
#include <vector>

namespace JesusASM {
    namespace Opcodes {
#       include "moduleweb/builder/opcodes.h"
    }

    using Opcode = Opcodes::moduleweb_opcodes;

    struct EnumOpcodesMember {
        Opcode opcode;
        std::string name;
        int stackPushes;
        int stackPops;
    };

    namespace EnumOpcodes {
        const EnumOpcodesMember& Get(Opcode opcode);
        const EnumOpcodesMember& Get(std::string_view name);
    }
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_OPCODES_H
