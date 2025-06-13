// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/FieldInsnNode.h"

#include <format>

namespace JesusASM::tree {

    FieldInsnNode::FieldInsnNode(Opcode opcode, const Name& owner, std::string_view name, std::string_view descriptor)
        : FieldInsnNode(opcode, owner.moduleName, owner.name, name, descriptor) {}

    FieldInsnNode::FieldInsnNode(Opcode opcode, std::string_view ownerModule, std::string_view owner,
                                 std::string_view name, std::string_view descriptor)
            : AbstractInsnNode(InsnType::FIELD, opcode)
            , mOwnerModule(ownerModule)
            , mOwner(owner)
            , mName(name)
            , mDescriptor(descriptor) {}

    FieldInsnNode::FieldInsnNode(Opcode opcode, std::string&& ownerModule, std::string&& owner, std::string&& name,
                                 std::string&& descriptor)
            : AbstractInsnNode(InsnType::FIELD, opcode)
            , mOwnerModule(std::move(ownerModule))
            , mOwner(std::move(owner))
            , mName(std::move(name))
            , mDescriptor(std::move(descriptor)) {}

    void FieldInsnNode::print(std::ostream& stream) const {
        stream << std::format("{} Field {}:{}:{}:{}", mOpcode.name, mOwnerModule, mOwner, mName, mDescriptor);
    }

    void FieldInsnNode::emit(moduleweb::InsnList& list) {
        list.fieldInsn(mOpcode.opcode, mOwnerModule, mOwner, mName, mDescriptor);
    }
}