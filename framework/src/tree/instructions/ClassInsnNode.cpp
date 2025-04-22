// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/ClassInsnNode.h"

#include <format>

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

    void ClassInsnNode::print(std::ostream& stream) const {
        stream << std::format("{} Class {}:{}", mOpcode.name, mModule, mName);
    }

    void ClassInsnNode::emit(moduleweb::InsnList& list) {
        list.classInsn(mOpcode.opcode, mModule, mName);
    }
}