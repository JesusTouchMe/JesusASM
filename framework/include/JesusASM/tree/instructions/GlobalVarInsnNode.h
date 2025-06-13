// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_GLOBALVARINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_GLOBALVARINSNNODE_H

#include "JesusASM/tree/AbstractInsnNode.h"

#include <string>

namespace JesusASM::tree {
    class GlobalVarInsnNode : public AbstractInsnNode {
    public:
        GlobalVarInsnNode(Opcode opcode, std::string_view module, std::string_view name, std::string_view descriptor);
        GlobalVarInsnNode(Opcode opcode, std::string&& module, std::string&& name, std::string&& descriptor);

        void print(std::ostream& stream) const override;

        void emit(moduleweb::InsnList& list) override;

    private:
        std::string mModule;
        std::string mName;
        std::string mDescriptor;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_GLOBALVARINSNNODE_H
