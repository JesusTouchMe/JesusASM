// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/instructions/LabelNode.h"

namespace JesusASM::tree {
    LabelNode::LabelNode(std::string_view name)
        : AbstractInsnNode(InsnType::LABEL, Opcodes::NOP)
        , mName(name) {
        checkName();
    }

    LabelNode::LabelNode(std::string&& name)
        : AbstractInsnNode(InsnType::LABEL, Opcodes::NOP)
        , mName(std::move(name)) {
        checkName();
    }

    std::string_view LabelNode::getName() const {
        return mName;
    }

    moduleweb::Label* LabelNode::getLabel(moduleweb::InsnList& list) {
        if (mLabel == nullptr) {
            mLabel = list.createLabel(mName);
        }

        return mLabel;
    }

    void LabelNode::addPredecessor(LabelNode* label) {
        mPredecessors.push_back(label);
    }

    void LabelNode::addSuccessor(LabelNode* label) {
        mSuccessors.push_back(label);
    }

    void LabelNode::emit(moduleweb::InsnList& list) {
        list.addLabel(getLabel(list));
    }

    void LabelNode::checkName() {
        static thread_local u32 index = 0;

        if (mName.empty()) {
            mName = ".L";
            mName += std::to_string(index++);
        }
    }
}