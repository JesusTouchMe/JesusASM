// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/InsnList.h"
#include "JesusASM/moduleweb-wrappers/InsnList.h"


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
        //TODO: implement
    }
}
