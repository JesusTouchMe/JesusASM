// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/InsnList.h"

#include "JesusASM/tree/instructions/JumpInsnNode.h"

#include "JesusASM/moduleweb-wrappers/InsnList.h"

#include <iostream>
#include <queue>
#include <stdexcept>
#include <unordered_map>

namespace JesusASM::tree {
    bool InsnList::contains(AbstractInsnNode* insn) const {
        AbstractInsnNode* i = mFirst.get();
        while (i != nullptr && i != insn) {
            i = i->getNext();
        }

        return i != nullptr;
    }

    LabelNode* InsnList::findLabel(std::string_view name) const {
        AbstractInsnNode* i = mFirst.get();
        while (i != nullptr) {
            if (i->mType == InsnType::LABEL) {
                auto label = static_cast<LabelNode*>(i);
                if (label->mName == name) return label;
            }

            i = i->mNext.get();
        }

        return nullptr;
    }

    void InsnList::add(std::unique_ptr<AbstractInsnNode> insn) {
        mSize++;

        if (mLast == nullptr) {
            mFirst = std::move(insn);
            mLast = mFirst.get();
        } else {
            mLast->mNext = std::move(insn);
            mLast->mNext->mPrev = mLast;
            mLast = mLast->mNext.get();
        }
    }

    void InsnList::add(InsnList& list) {
        if (list.mSize == 0) return;

        mSize += list.mSize;

        if (mLast == nullptr) {
            mFirst = std::move(list.mFirst);
            mLast = list.mLast;
        } else {
            mLast->mNext = std::move(list.mFirst);
            mLast->mNext->mPrev = mLast;
            mLast = list.mLast;
        }

        list.clear();
    }

    void InsnList::addFront(std::unique_ptr<AbstractInsnNode> insn) {
        mSize++;

        if (mFirst == nullptr) {
            mFirst = std::move(insn);
            mLast = mFirst.get();
        } else {
            insn->mNext = std::move(mFirst);
            mFirst = std::move(insn);
            mFirst->mNext->mPrev = mFirst.get();
        }
    }

    void InsnList::addFront(InsnList& list) {
        if (list.mSize == 0) return;

        mSize += list.mSize;

        if (mFirst == nullptr) {
            mFirst = std::move(list.mFirst);
            mLast = list.mLast;
        } else {
            AbstractInsnNode* node = list.mLast;
            mFirst->mPrev = node;
            node->mNext = std::move(mFirst);
            mFirst = std::move(list.mFirst);
        }
    }

    void InsnList::insert(AbstractInsnNode* location, std::unique_ptr<AbstractInsnNode> insn) {
        mSize++;

        auto next = std::move(location->mNext);

        if (next == nullptr) {
            mLast = insn.get();
        } else {
            next->mPrev = insn.get();
        }

        location->mNext = std::move(insn);
        location->mNext->mNext = std::move(next);
        location->mNext->mPrev = location;
    }

    void InsnList::insert(AbstractInsnNode* location, InsnList& list) {
        if (list.mSize == 0) return;

        mSize += list.mSize;

        auto next = std::move(location->mNext);

        if (next == nullptr) {
            mLast = list.mLast;
        } else {
            next->mPrev = list.mLast;
        }

        location->mNext = std::move(list.mFirst);
        list.mLast->mNext = std::move(next);
        location->mNext->mPrev = location;

        list.clear();
    }

    void InsnList::insertBefore(AbstractInsnNode* location, std::unique_ptr<AbstractInsnNode> insn) {
        mSize++;

        insn->mPrev = location->mPrev;
        insn->mNext = std::move(location->mPrev != nullptr ? location->mPrev->mNext : mFirst);

        if (location->mPrev == nullptr) {
            mFirst = std::move(insn);
            location->mPrev = mFirst.get();
        } else {
            location->mPrev->mNext = std::move(insn);
            location->mPrev = location->mPrev->mNext.get();
        }
    }

    void InsnList::insertBefore(AbstractInsnNode* location, InsnList& list) {
        if (list.mSize == 0) return;

        mSize += list.mSize;

        if (location->mPrev == nullptr) {
            list.mLast->mNext = std::move(mFirst);
            mFirst = std::move(list.mFirst);
        } else {
            list.mLast->mNext = std::move(location->mPrev->mNext);
            location->mPrev->mNext = std::move(list.mFirst);
        }

        if (list.mLast->mNext != nullptr) {
            list.mLast->mNext->mPrev = list.mLast;
        }

        location->mPrev = list.mLast;

        list.clear();
    }

    void InsnList::remove(AbstractInsnNode* insn) {
        mSize--;

        if (insn == mFirst.get()) {
            mFirst = std::move(mFirst->mNext);
            if (mFirst != nullptr) {
                mFirst->mPrev = nullptr;
            } else {
                mLast = nullptr;
            }

            return;
        }

        if (insn == mLast) {
            mLast = mLast->mPrev;
            mLast->mNext = nullptr;
            return;
        }

        if (insn->mNext != nullptr) {
            insn->mNext->mPrev = insn->mPrev;
        }

        if (insn->mPrev != nullptr) {
            insn->mPrev->mNext = std::move(insn->mNext);
        }
    }

    std::unique_ptr<LabelNode> InsnList::removeLabel(std::string_view name) {
        auto* i = &mFirst;
        while (*i) {
            if ((*i)->mType == InsnType::LABEL) {
                auto label = static_cast<LabelNode*>(i->get());
                if (label->mName == name) {
                    label = static_cast<LabelNode*>(i->release());
                    remove(label);
                    return std::unique_ptr<LabelNode>(label);
                }
            }

            i = &(*i)->mNext;
        }

        return nullptr;
    }

    void InsnList::clear() {
        mSize = 0;
        mFirst = nullptr;
        mLast = nullptr;
    }

    void InsnList::print(std::ostream& stream) const {
        AbstractInsnNode* node = mFirst.get();
        while (node != nullptr) {
            if (node->getType() == InsnType::LABEL) stream << "  ";
            else stream << "    ";
            node->print(stream);
            stream << "\n";

            node = node->getNext();
        }
    }

    void InsnList::emit(moduleweb::InsnList& list) {
        if (mSize == 0) return;

        LabelNode* currentLabel = nullptr;

        if (mFirst->getType() != InsnType::LABEL) {
            addFront(std::make_unique<LabelNode>());
        }

        analyzeFallthroughLabels();

        AbstractInsnNode* node = mFirst.get();
        while (node != nullptr) {
            if (node->getType() == InsnType::LABEL) {
                currentLabel = static_cast<LabelNode*>(node);
            }

            node->mLabel = currentLabel;

            node->preEmit(list);

            node = node->getNext();
        }

        std::unordered_map<LabelNode*, i32> stackDepthMap;
        std::queue<LabelNode*> worklist;

        stackDepthMap[static_cast<LabelNode*>(mFirst.get())] = 0;
        worklist.push(static_cast<LabelNode*>(mFirst.get()));

        while (!worklist.empty()) {
            auto label = worklist.front();
            worklist.pop();

            i32 currentDepth = stackDepthMap[label];
            i32 newDepth = currentDepth;

            for (auto pred : label->mPredecessors) {
                if (stackDepthMap.contains(pred)) {
                    newDepth = std::max(newDepth, stackDepthMap[pred]);
                }
            }

            AbstractInsnNode* it = label;
            while (it != nullptr && it->mLabel == label) { // same as doing for auto insn : label.getInstructions() if label contained its own list of instructions
                newDepth -= it->getStackPops();
                newDepth += it->getStackPushes();

                if (newDepth < 0) {
                    throw std::runtime_error("Stack underflow");
                }

                list.setStackDepth(newDepth);

                if (it->getType() == InsnType::JUMP) {
                    auto jump = static_cast<JumpInsnNode*>(it);

                    if (jump->mOpcode.opcode == Opcodes::JMP) { // unconditional. literally just ignore the rest of the instructions
                        LabelNode* dest = jump->mDestination;
                        if (!stackDepthMap.contains(dest) || newDepth > stackDepthMap[dest]) {
                            stackDepthMap[dest] = newDepth;
                            worklist.push(dest);
                        }

                        break;
                    } else {
                        LabelNode* target = jump->mDestination;
                        LabelNode* fallThrough = jump->getNext() == nullptr ? nullptr : jump->getNext()->mLabel;

                        if (!stackDepthMap.contains(target) || newDepth > stackDepthMap[target]) {
                            stackDepthMap[target] = newDepth;
                            worklist.push(target);
                        }
                        if (fallThrough != nullptr) {
                            if (!stackDepthMap.contains(fallThrough) || newDepth > stackDepthMap[fallThrough]) {
                                stackDepthMap[fallThrough] = newDepth;
                                worklist.push(fallThrough);
                            }
                        }
                    }
                }

                it = it->getNext();
            }

            for (auto successor : label->mSuccessors) {
                if (!stackDepthMap.contains(successor) || newDepth > stackDepthMap[successor]) {
                    stackDepthMap[successor] = newDepth;
                    worklist.push(successor);
                }
            }
        }

        node = mFirst.get();
        while (node != nullptr) {
            node->emit(list);
            node = node->getNext();
        }
    }

    void InsnList::analyzeFallthroughLabels() {
        tree::LabelNode* prevLabel = nullptr;
        tree::AbstractInsnNode* prevInsn = nullptr;

        for (tree::AbstractInsnNode* it = mFirst.get(); it != nullptr; it = it->getNext()) {
            if (it->getType() == InsnType::LABEL) {
                auto currentLabel = static_cast<tree::LabelNode*>(it);

                if (prevLabel != nullptr && prevInsn != nullptr && !prevInsn->isJump()) {
                    prevLabel->addSuccessor(currentLabel);
                    currentLabel->addPredecessor(prevLabel);
                }

                prevLabel = currentLabel;
            } else {
                prevInsn = it;
            }
        }
    }
}
