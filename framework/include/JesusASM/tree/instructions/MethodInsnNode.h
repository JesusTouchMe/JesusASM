// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_METHODINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_METHODINSNNODE_H 1

#include "JesusASM/Name.h"

#include "JesusASM/tree/AbstractInsnNode.h"

namespace JesusASM::tree {
    class MethodInsnNode : public AbstractInsnNode {
    public:
        MethodInsnNode(Opcode opcode, std::string ownerModule, std::string owner, std::string name, std::string descriptor);

        int getStackPushes() const override;
        int getStackPops() const override;

        void print(std::ostream& stream) const override;

        void emit(moduleweb::InsnList& list) override;

    private:
        std::string mOwnerModule;
        std::string mOwner;
        std::string mName;
        std::string mDescriptor;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_METHODINSNNODE_H