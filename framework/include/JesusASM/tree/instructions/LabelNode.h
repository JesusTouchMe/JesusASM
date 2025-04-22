// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_LABELNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_LABELNODE_H

#include "JesusASM/tree/AbstractInsnNode.h"

#include <string>
#include <vector>

namespace JesusASM::tree {
    class LabelNode : public AbstractInsnNode {
    friend class InsnList;
    public:
        LabelNode(std::string_view name = "");
        LabelNode(std::string&& name);

        std::string_view getName() const;
        moduleweb::Label* getLabel(moduleweb::InsnList& list);

        void addPredecessor(LabelNode* label);
        void addSuccessor(LabelNode* label);

        void print(std::ostream& stream) const override;

        void emit(moduleweb::InsnList& list) override;

    private:
        std::string mName;
        std::vector<LabelNode*> mPredecessors;
        std::vector<LabelNode*> mSuccessors;

        moduleweb::Label* mLabel = nullptr;

        void checkName();
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSTRUCTIONS_LABELNODE_H
