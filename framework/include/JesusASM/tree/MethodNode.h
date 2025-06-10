// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_METHODNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_METHODNODE_H 1

#include "JesusASM/Attribute.h"

#include "JesusASM/tree/FunctionNode.h"

#include "JesusASM/moduleweb-wrappers/MethodBuilder.h"

namespace JesusASM::tree {
    struct FunctionSymbol {
        std::string moduleName;
        std::string name;
        std::string descriptor;

        bool empty() const { return moduleName.empty() || name.empty() || descriptor.empty(); }
    };

    struct MethodNode {
        u16 modifiers;
        std::string name;
        std::string descriptor;

        FunctionSymbol function;

        std::vector<std::unique_ptr<IAttribute>> attributes;

        MethodNode(u16 modifiers, std::string name, std::string descriptor, FunctionSymbol function);

        void print(std::ostream& stream) const;

        void emit(moduleweb::MethodBuilder& builder);
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_METHODNODE_H