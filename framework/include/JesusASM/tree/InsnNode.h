// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSNNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSNNODE_H 1

#include "JesusASM/Opcodes.h"

#include "moduleweb/types.h"

#include <memory>

namespace JesusASM::tree {
    class InsnList;

    enum class InsnType {

    };

    class InsnNode {
    friend class InsnList;
    public:
        virtual ~InsnNode() = default;

        [[nodiscard]] Opcode getOpcode() const { return mOpcode; }
        [[nodiscard]] virtual InsnType getType() const = 0;

        [[nodiscard]] InsnNode* getNext() const { return mNext.get(); }
        [[nodiscard]] InsnNode* getPrev() const { return mPrev; }

    protected:
        Opcode mOpcode;

        explicit InsnNode(Opcode opcode)
            : mOpcode(opcode) {}

    private:
        std::unique_ptr<InsnNode> mNext;
        InsnNode* mPrev = nullptr;
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSNNODE_H
