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

        if (insn->mPrev == nullptr) {
            mFirst = std::move(insn->mNext);
            if (mFirst != nullptr) {
                mFirst->mPrev = nullptr;
            }
        } else {
            insn->mPrev->mNext = std::move(insn->mNext);
            if (insn->mPrev->mNext != nullptr) {
                insn->mPrev->mNext->mPrev = insn->mPrev;
            }
        }

        if (insn->mNext == nullptr) {
            mLast = insn->mPrev;
        } else {
            insn->mNext->mPrev = insn->mPrev;
        }
    }

    void InsnList::clear() {
        mSize = 0;
        mFirst = nullptr;
        mLast = nullptr;
    }

    void InsnList::emit(moduleweb::InsnList& list) {
        if (mSize == 0) return;

        if (mFirst->getType() != InsnType::LABEL) {
            addFront(std::make_unique<LabelNode>());
        }

        LabelNode* currentLabel = nullptr;

        AbstractInsnNode* node = mFirst.get();
        while (node != nullptr) {
            if (node->getType() == InsnType::LABEL) {
                currentLabel = static_cast<LabelNode*>(node);
            } else {
                node->mLabel = currentLabel;
            }

            node->preEmit(list);

            node = node->getNext();
        }

        std::unordered_map<AbstractInsnNode*, i32> stackDepthMap;
        std::unordered_map<AbstractInsnNode*, i32> predecessorCount;
        std::queue<AbstractInsnNode*> worklist;
        std::queue<AbstractInsnNode*> discoveryQueue;

        discoveryQueue.push(mFirst.get());

        while (!discoveryQueue.empty()) {
            AbstractInsnNode* insn = discoveryQueue.front();
            discoveryQueue.pop();

            if (predecessorCount.find(insn) != predecessorCount.end()) {
                continue;
            }

            predecessorCount[insn] = 0;

            if (insn->getType() == InsnType::LABEL) {
                auto label = static_cast<LabelNode*>(insn);
                predecessorCount[insn] = label->mPredecessors.size();

                for (auto successor : label->mSuccessors) {
                    discoveryQueue.push(successor);
                }
            }

            if (insn->getType() == InsnType::JUMP) {
                auto jump = static_cast<JumpInsnNode*>(insn);
                discoveryQueue.push(jump->mDestination);

                if (jump->mOpcode != Opcodes::JMP && jump->getNext() != nullptr) {
                    discoveryQueue.push(jump->getNext());
                    predecessorCount[jump->getNext()]++;
                }
            } else if (insn->getNext() != nullptr) {
                discoveryQueue.push(insn->getNext());
                predecessorCount[insn->getNext()]++;
            }
        }

        stackDepthMap[mFirst.get()] = 0;
        worklist.push(mFirst.get());

        while (!worklist.empty()) {
            AbstractInsnNode* insn = worklist.front();
            worklist.pop();

            i32 currentDepth = stackDepthMap[insn];
            i32 newDepth = currentDepth - insn->getStackPops() + insn->getStackPushes();
            if (newDepth < 0) {
                throw std::runtime_error("Stack underflow");
            }

            list.setStackDepth(newDepth);

            std::vector<AbstractInsnNode*> successors;

            if (insn->getType() == InsnType::LABEL) {
                auto label = static_cast<LabelNode*>(insn);

                i32 mergedDepth = (stackDepthMap.find(insn) != stackDepthMap.end())
                                  ? stackDepthMap[insn]
                                  : newDepth;

                for (auto pred : label->mPredecessors) {
                    if (stackDepthMap.find(pred) != stackDepthMap.end()) {
                        mergedDepth = max(mergedDepth, stackDepthMap[pred]);
                    }
                }

                newDepth = mergedDepth;

                for (auto successor : label->mSuccessors) {
                    if (stackDepthMap.find(successor) == stackDepthMap.end()
                        || newDepth > stackDepthMap[successor]) {
                        stackDepthMap[successor] = newDepth;
                        worklist.push(successor);
                    } else {
                        worklist.push(successor);
                    }
                }
            }

            if (insn->getType() == InsnType::JUMP) {
                auto jump = static_cast<JumpInsnNode*>(insn);

                if (stackDepthMap.find(jump->mDestination) == stackDepthMap.end()
                    || newDepth > stackDepthMap[jump->mDestination]) {
                    stackDepthMap[jump->mDestination] = newDepth;
                    worklist.push(jump->mDestination);
                }

                if (jump->mOpcode != Opcodes::JMP && jump->getNext() != nullptr) { // for conditional jumps, also process the "false" block
                    successors.push_back(jump->getNext());
                }
            } else if (insn->getNext() != nullptr) {
                successors.push_back(insn->getNext());
            }

            for (auto successor : successors) {
                if (stackDepthMap.find(successor) == stackDepthMap.end()
                    || newDepth > stackDepthMap[successor]) {
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
}
