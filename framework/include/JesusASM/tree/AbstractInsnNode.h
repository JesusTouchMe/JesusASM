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
        JUMP,
        VAR,
        INT,
    };

    class AbstractInsnNode {
    friend class InsnList;
    public:
        virtual ~AbstractInsnNode() = default;

        [[nodiscard]] Opcode getOpcode() const { return mOpcode; }
        [[nodiscard]] InsnType getType() const { return mType; };

        [[nodiscard]] AbstractInsnNode* getNext() const { return mNext.get(); }
        [[nodiscard]] AbstractInsnNode* getPrev() const { return mPrev; }

        [[nodiscard]] virtual i32 getStackPushes() const { return 0; }
        [[nodiscard]] virtual i32 getStackPops() const { return 0; }

        virtual void emit(moduleweb::InsnList& list) = 0;
        virtual void preEmit(moduleweb::InsnList& list) {}

    protected:
        InsnType mType;
        Opcode mOpcode;

        LabelNode* mLabel = nullptr; // the label or "basic block" this node exists in

        explicit AbstractInsnNode(InsnType type, Opcode opcode)
            : mType(type)
            , mOpcode(opcode) {}

    private:
        std::unique_ptr<AbstractInsnNode> mNext;
        AbstractInsnNode* mPrev = nullptr;
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_ABSTRACTINSNNODE_H
