// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/ClassInsnNode.h"

namespace JesusASM::tree {
    ClassInsnNode::ClassInsnNode(Opcode opcode, const Name& qualifiedName)
        : ClassInsnNode(opcode, qualifiedName.moduleName, qualifiedName.name) {}

    ClassInsnNode::ClassInsnNode(Opcode opcode, std::string_view module, std::string_view name)
        : AbstractInsnNode(InsnType::CLASS, opcode)
        , mModule(module)
        , mName(name) {}

    ClassInsnNode::ClassInsnNode(Opcode opcode, std::string&& module, std::string&& name)
        : AbstractInsnNode(InsnType::CLASS, opcode)
        , mModule(std::move(module))
        , mName(std::move(name)) {}

    i32 ClassInsnNode::getStackPushes() const {
        if (mOpcode == Opcodes::ISINSTANCE) {
            return 1; // true or false
        }

        return 2;
    }

    i32 ClassInsnNode::getStackPops() const {
        if (mOpcode == Opcodes::ISINSTANCE) {
            return 2; // the checked object
        }

        if (mOpcode == Opcodes::RNEWARRAY) {
            return 1; // length
        }

        return 0;
    }

    void ClassInsnNode::emit(moduleweb::InsnList& list) {
        list.classInsn(mOpcode, mModule, mName);
    }
}