// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_CALLINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_CALLINSNNODE_H

#include "JesusASM/tree/AbstractInsnNode.h"

#include <string>

namespace JesusASM::tree {
    class CallInsnNode : public AbstractInsnNode {
    public:
        CallInsnNode(Opcode opcode, std::string_view module, std::string_view name, std::string_view descriptor);
        CallInsnNode(Opcode opcode, std::string&& module, std::string&& name, std::string&& descriptor);

        int getStackPushes() const override;
        int getStackPops() const override;

        void emit(moduleweb::InsnList& list) override;

    private:
        std::string mModule;
        std::string mName;
        std::string mDescriptor;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_CALLINSNNODE_H
