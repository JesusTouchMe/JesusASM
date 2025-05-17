// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/ModuleNode.h"

#include <format>
#include <stdexcept>

namespace JesusASM::tree {
    ModuleNode::ModuleNode(u16 version, std::string_view name)
        : version(version)
        , name(name) {}

    ModuleNode::ModuleNode(u16 version, std::string&& name)
        : version(version)
        , name(std::move(name)) {}

    void ModuleNode::print(std::ostream& stream) const {
        stream << std::format("module {} using v{}\n\n", name, version);

        for (const auto& classNode : classes) {
            classNode->print(stream);
            stream << "\n\n";
        }

        for (const auto& function : functions) {
            function->print(stream);
            stream << "\n\n";
        }
    }

    void ModuleNode::emit(moduleweb::ModuleBuilder& builder, moduleweb::ModuleInfo& info) {
        if (name.empty()) {
            throw std::runtime_error("Module name is empty");
        }

        moduleweb::AttributeBuilder attributeBuilder(builder);
        for (auto& attr : attributes) {
            attr->emit(attributeBuilder);
        }

        moduleweb::ClassBuilder classBuilder(builder);
        for (auto& clas : classes) {
            clas->emit(classBuilder);
        }

        moduleweb::GlobalVarBuilder globalVarBuilder(builder);
        for (auto& global : globals) {
            global->emit(globalVarBuilder);
        }

        moduleweb::FunctionBuilder functionBuilder(builder);
        for (auto& func : functions) {
            func->emit(functionBuilder);
        }

        builder
            .version(version)
            .name(name)
            .build(info);
    }
}