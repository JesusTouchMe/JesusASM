// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/MethodNode.h"

#include <format>
#include <stdexcept>

namespace JesusASM::tree {
    MethodNode::MethodNode(u16 modifiers, std::string name, std::string descriptor, FunctionSymbol function)
        : modifiers(modifiers)
        , name(std::move(name))
        , descriptor(std::move(descriptor))
        , function(std::move(function)) {}

    void MethodNode::print(std::ostream& stream) const {
        stream << std::format("method {}:{} callee={}::{}:{}", name, descriptor, function.moduleName, function.name, function.descriptor);
    }

    void MethodNode::emit(moduleweb::MethodBuilder& builder) {
        if (name.empty() || descriptor.empty() || function.empty()) {
            throw std::runtime_error("Method name or descriptor or function name is empty");
        }

        moduleweb::AttributeBuilder attributeBuilder(builder);
        for (auto& attr : attributes) {
            attr->emit(attributeBuilder);
        }

        builder
            .modifiers(modifiers)
            .descriptor(name, descriptor)
            .function(function.moduleName, function.name, function.descriptor)
            .build();
    }
}
