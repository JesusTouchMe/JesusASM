// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_FIELDNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_FIELDNODE_H 1

#include "JesusASM/Attribute.h"

#include "JesusASM/moduleweb-wrappers/FieldBuilder.h"

#include "moduleweb/field_info.h"

#include <memory>
#include <vector>

namespace JesusASM::tree {
    struct FieldNode {
        u16 modifiers;
        std::string name;
        std::string descriptor;

        std::vector<std::unique_ptr<IAttribute>> attributes;

        FieldNode(u16 modifiers, std::string_view name, std::string_view descriptor);
        FieldNode(u16 modifiers, std::string&& name, std::string&& descriptor);

        void print(std::ostream& stream) const;

        void emit(moduleweb::FieldBuilder& builder);
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_FIELDNODE_H
