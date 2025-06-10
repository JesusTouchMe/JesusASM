// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_CLASSNODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_CLASSNODE_H 1

#include "JesusASM/Name.h"

#include "JesusASM/moduleweb-wrappers/ClassBuilder.h"

#include "JesusASM/tree/FieldNode.h"
#include "JesusASM/tree/MethodNode.h"

#include "moduleweb/class_info.h"

namespace JesusASM::tree {
    struct ClassNode {
        u16 modifiers = 0;
        std::string name;
        Name superClass;

        std::vector<std::unique_ptr<IAttribute>> attributes;
        std::vector<std::unique_ptr<FieldNode>> fields;
        std::vector<std::unique_ptr<MethodNode>> methods;

        ClassNode() = default;
        ClassNode(u16 modifiers, std::string_view name, Name superClass);
        ClassNode(u16 modifiers, std::string&& name, Name&& superClass);

        void print(std::ostream& stream) const;

        void emit(moduleweb::ClassBuilder& builder);
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_CLASSNODE_H
