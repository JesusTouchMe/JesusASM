// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/InsnList.h"

namespace JesusASM::tree {
    bool InsnList::contains(InsnNode* insn) const {
        InsnNode* i = mFirst.get();
        while (i != nullptr && i != insn) {
            i = i->getNext();
        }

        return i != nullptr;
    }

    void InsnList::add(std::unique_ptr<InsnNode> insn) {
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

    void InsnList::addFront(std::unique_ptr<InsnNode> insn) {
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
            InsnNode* node = list.mLast;
            mFirst->mPrev = node;
            node->mNext = std::move(mFirst);
            mFirst = std::move(list.mFirst);
        }
    }

    void InsnList::insert(InsnNode* location, std::unique_ptr<InsnNode> insn) {
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

    void InsnList::insert(InsnNode* location, InsnList& list) {
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

    void InsnList::insertBefore(InsnNode* location, std::unique_ptr<InsnNode> insn) {
        mSize++;

        auto prev = location->mPrev;
        InsnNode* node;

        if (prev == nullptr) {
            mFirst = std::move(insn);
            node = mFirst.get();
        } else {
            prev->mNext = std::move(insn);
            node = prev->mNext.get();
        }

        location->mPrev = node;
        node->mNext =
    }

    void InsnList::insertBefore(InsnNode* location, InsnList& list) {

    }

    void InsnList::remove(InsnNode* insn) {

    }

    void InsnList::clear() {

    }
}