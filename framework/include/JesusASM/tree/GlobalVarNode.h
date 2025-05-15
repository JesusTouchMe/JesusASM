// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_GLOBALVARNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_GLOBALVARNODE_H

#include "JesusASM/Attribute.h"

#include "JesusASM/moduleweb-wrappers/GlobalVarBuilder.h"

#include <memory>
#include <vector>

namespace JesusASM::tree {
    struct GlobalVarNode {
        u16 modifiers;
        std::string name;
        std::string descriptor;

        std::vector<std::unique_ptr<IAttribute>> attributes;

        GlobalVarNode() = default;
        GlobalVarNode(u16 modifiers, std::string_view name, std::string_view descriptor);
        GlobalVarNode(u16 modifiers, std::string&& name, std::string&& descriptor);

        void print(std::ostream& stream) const;

        void emit(moduleweb::GlobalVarBuilder& builder);
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_GLOBALVARNODE_H
