// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_ABSTRACTINSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_ABSTRACTINSNNODE_H 1

#include "JesusASM/Opcodes.h"

#include "JesusASM/moduleweb-wrappers/InsnList.h"

#include "moduleweb/types.h"

#include <memory>

namespace JesusASM::tree {
    class InsnList;
    class LabelNode;

    enum class InsnType {
        INSN,
        CALL,
        LABEL,
        LDC,
        JUMP,
        CLASS,
        FIELD,
        VAR,
        INT,
    };

    class AbstractInsnNode {
    friend class InsnList;
    public:
        virtual ~AbstractInsnNode() = default;

        [[nodiscard]] const EnumOpcodesMember& getOpcode() const { return mOpcode; }
        [[nodiscard]] InsnType getType() const { return mType; };

        [[nodiscard]] AbstractInsnNode* getNext() const { return mNext.get(); }
        [[nodiscard]] AbstractInsnNode* getPrev() const { return mPrev; }

        [[nodiscard]] virtual int getStackPushes() const { return mOpcode.stackPushes; }
        [[nodiscard]] virtual int getStackPops() const { return mOpcode.stackPops; }

        [[nodiscard]] bool isJump() const {
            if (mType == InsnType::JUMP) return true;

            switch (mOpcode.opcode) {
                case Opcodes::RETURN:
                case Opcodes::IRETURN:
                case Opcodes::LRETURN:
                case Opcodes::HRETURN:
                case Opcodes::RRETURN:
                    return true;
            }

            return false;
        }

        virtual void print(std::ostream& stream) const = 0;

        virtual void emit(moduleweb::InsnList& list) = 0;
        virtual void preEmit(moduleweb::InsnList& list) {}

    protected:
        InsnType mType;
        const EnumOpcodesMember& mOpcode;

        LabelNode* mLabel = nullptr; // the label or "basic block" this node exists in

        explicit AbstractInsnNode(InsnType type, Opcode opcode)
            : mType(type)
            , mOpcode(EnumOpcodes::Get(opcode)) {}

    private:
        std::unique_ptr<AbstractInsnNode> mNext;
        AbstractInsnNode* mPrev = nullptr;
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_ABSTRACTINSNNODE_H
