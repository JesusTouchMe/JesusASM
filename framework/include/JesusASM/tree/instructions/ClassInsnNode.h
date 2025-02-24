// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_CLASSINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_CLASSINSNNODE_H

#include "JesusASM/Name.h"

#include "JesusASM/tree/AbstractInsnNode.h"

namespace JesusASM::tree {
    class ClassInsnNode : public AbstractInsnNode {
    public:
        ClassInsnNode(Opcode opcode, const Name& qualifiedName);
        ClassInsnNode(Opcode opcode, std::string_view module, std::string_view name);
        ClassInsnNode(Opcode opcode, std::string&& module, std::string&& name);

        i32 getStackPushes() const override;

        i32 getStackPops() const override;

        void emit(moduleweb::InsnList& list) override;

    private:
        std::string mModule;
        std::string mName;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_CLASSINSNNODE_H
