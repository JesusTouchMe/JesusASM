// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/FieldInsnNode.h"

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

    i32 FieldInsnNode::getStackPushes() const {
        if (mOpcode == Opcodes::GETFIELD) {
            char c = mDescriptor[0];
            switch (c) {
                case 'B':
                case 'S':
                case 'I':
                case 'C':
                case 'Z':
                    return 1;

                case 'R':
                case '[':
                case 'H':
                case 'L':
                case 'D':
                    return 2;

                default:
                    throw std::runtime_error("Bad descriptor");
            }
        }

        return 0;
    }

    i32 FieldInsnNode::getStackPops() const {
        i32 pops = 2; // the object

        if (mOpcode == Opcodes::SETFIELD) {
            char c = mDescriptor[0];
            switch (c) {
                case 'B':
                case 'S':
                case 'I':
                case 'C':
                case 'Z':
                    pops += 1;
                    break;

                case 'R':
                case '[':
                case 'H':
                case 'L':
                case 'D':
                    pops += 2;
                    break;

                default:
                    throw std::runtime_error("Bad descriptor");
            }
        }

        return pops;
    }

    void FieldInsnNode::emit(moduleweb::InsnList& list) {
        list.fieldInsn(mOpcode, mOwnerModule, mOwner, mName, mDescriptor);
    }
}