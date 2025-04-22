// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_MODULENODE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_MODULENODE_H 1

#include "JesusASM/tree/ClassNode.h"
#include "JesusASM/tree/FunctionNode.h"

#include "JesusASM/moduleweb-wrappers/ModuleBuilder.h"

#include "moduleweb/module_info.h"

#include <memory>
#include <string>

namespace JesusASM::tree {
    struct ModuleNode {
        u16 version;
        std::string name;

        std::vector<std::unique_ptr<IAttribute>> attributes;
        std::vector<std::unique_ptr<ClassNode>> classes;
        std::vector<std::unique_ptr<FunctionNode>> functions;

        ModuleNode() = default;
        ModuleNode(u16 version, std::string_view name);
        ModuleNode(u16 version, std::string&& name);

        void print(std::ostream& stream) const;

        void emit(moduleweb::ModuleBuilder& builder, moduleweb::ModuleInfo& info);
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TREE_MODULENODE_H
