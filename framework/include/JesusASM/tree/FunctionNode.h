// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_FUNCTIONNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_FUNCTIONNODE_H 1

#include "JesusASM/Attribute.h"

#include "JesusASM/moduleweb-wrappers/FunctionBuilder.h"

#include <memory>
#include <vector>

namespace JesusASM::tree {
    struct FunctionNode {
        u16 modifiers;
        std::string name;
        std::string descriptor;

        std::vector<std::unique_ptr<Attribute>> attributes;

        FunctionNode() = default;
        FunctionNode(u16 modifiers, std::string_view name, std::string_view descriptor);
        FunctionNode(u16 modifiers, std::string&& name, std::string&& descriptor);

        void emit(moduleweb::FunctionBuilder& builder);
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_FUNCTIONNODE_H
