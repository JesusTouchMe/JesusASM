// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_FIELDINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_FIELDINSNNODE_H

#include "JesusASM/Name.h"

#include "JesusASM/tree/AbstractInsnNode.h"

namespace JesusASM::tree {
    class FieldInsnNode : public AbstractInsnNode {
    public:
        FieldInsnNode(Opcode opcode, const Name& owner, std::string_view name, std::string_view descriptor);
        FieldInsnNode(Opcode opcode, std::string_view ownerModule, std::string_view owner, std::string_view name, std::string_view descriptor);
        FieldInsnNode(Opcode opcode, std::string&& ownerModule, std::string&& owner, std::string&& name, std::string&& descriptor);

        i32 getStackPushes() const override;

        i32 getStackPops() const override;

        void emit(moduleweb::InsnList& list) override;

    private:
        std::string mOwnerModule;
        std::string mOwner;
        std::string mName;
        std::string mDescriptor;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_FIELDINSNNODE_H
