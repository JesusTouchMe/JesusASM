// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_LDCINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_LDCINSNNODE_H 1

#include "JesusASM/tree/AbstractInsnNode.h"

#include <string>

namespace JesusASM::tree {
    class LdcInsnNode : public AbstractInsnNode {
    public:
        LdcInsnNode(std::string_view value);
        LdcInsnNode(std::string&& value);

        int getStackPushes() const override;
        int getStackPops() const override;

        void emit(moduleweb::InsnList& list) override;

    private:
        std::string mValue;
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_LDCINSNNODE_H
