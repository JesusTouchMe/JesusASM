// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSNLIST_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSNLIST_H 1

#include "JesusASM/tree/AbstractInsnNode.h"

#include <iterator>

namespace JesusASM::tree {
    class InsnList {
    public:
        class Iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = AbstractInsnNode;
            using pointer = AbstractInsnNode*;
            using reference = AbstractInsnNode&;

            explicit Iterator(pointer node) : mCurrent(node) {}

            reference operator*() const { return *mCurrent; }
            pointer operator->() const { return mCurrent; }

            Iterator& operator++() { // Prefix increment
                if (mCurrent) mCurrent = mCurrent->getNext();
                return *this;
            }

            Iterator operator++(int) { // Postfix increment
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const Iterator& other) const { return mCurrent == other.mCurrent; }
            bool operator!=(const Iterator& other) const { return !(*this == other); }

        private:
            pointer mCurrent;
        };

        class ReverseIterator {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = AbstractInsnNode;
            using pointer = AbstractInsnNode*;
            using reference = AbstractInsnNode&;

            explicit ReverseIterator(pointer node) : mCurrent(node) {}

            reference operator*() const { return *mCurrent; }
            pointer operator->() const { return mCurrent; }

            ReverseIterator& operator++() { // Move to previous node
                if (mCurrent) mCurrent = mCurrent->getPrev();
                return *this;
            }

            ReverseIterator operator++(int) { // Postfix increment
                ReverseIterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const ReverseIterator& other) const { return mCurrent == other.mCurrent; }
            bool operator!=(const ReverseIterator& other) const { return !(*this == other); }

        private:
            pointer mCurrent;
        };

        [[nodiscard]] Iterator begin() const { return Iterator(mFirst.get()); }
        [[nodiscard]] Iterator end() const { return Iterator(nullptr); }

        [[nodiscard]] ReverseIterator rbegin() const { return ReverseIterator(mLast); }
        [[nodiscard]] ReverseIterator rend() const { return ReverseIterator(nullptr); }

        [[nodiscard]] AbstractInsnNode* getFirst() const { return mFirst.get(); }
        [[nodiscard]] AbstractInsnNode* getLast() const { return mLast; }

        [[nodiscard]] std::size_t getSize() const { return mSize; }

        [[nodiscard]] bool contains(AbstractInsnNode* insn) const;

        void add(std::unique_ptr<AbstractInsnNode> insn);
        void add(InsnList& list);

        void addFront(std::unique_ptr<AbstractInsnNode> insn);
        void addFront(InsnList& list);

        void insert(AbstractInsnNode* location, std::unique_ptr<AbstractInsnNode> insn);
        void insert(AbstractInsnNode* location, InsnList& list);

        void insertBefore(AbstractInsnNode* location, std::unique_ptr<AbstractInsnNode> insn);
        void insertBefore(AbstractInsnNode* location, InsnList& list);

        void remove(AbstractInsnNode* insn);

        void clear();

        void emit(moduleweb::InsnList& list);

    private:
        std::unique_ptr<AbstractInsnNode> mFirst = nullptr;
        AbstractInsnNode* mLast = nullptr;

        std::size_t mSize;
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_INSNLIST_H
