// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/LdcInsnNode.h"

namespace JesusASM::tree {
    LdcInsnNode::LdcInsnNode(std::string_view value)
        : AbstractInsnNode(InsnType::LDC, Opcodes::LDC)
        , mValue(value) {}

    LdcInsnNode::LdcInsnNode(std::string&& value)
        : AbstractInsnNode(InsnType::LDC, Opcodes::LDC)
        , mValue(std::move(value)) {}

    i32 LdcInsnNode::getStackPushes() const {
        return 2;
    }

    i32 LdcInsnNode::getStackPops() const {
        return 0;
    }

    void LdcInsnNode::emit(moduleweb::InsnList& list) {
        list.ldcInsn(mValue);
    }
}