// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/FunctionNode.h"

#include <stdexcept>

namespace JesusASM::tree {

    FunctionNode::FunctionNode(u16 modifiers, std::string_view name, std::string_view descriptor)
        : modifiers(modifiers)
        , name(name)
        , descriptor(descriptor) {}

    FunctionNode::FunctionNode(u16 modifiers, std::string&& name, std::string&& descriptor)
        : modifiers(modifiers)
        , name(std::move(name))
        , descriptor(std::move(descriptor)) {}

    void FunctionNode::emit(moduleweb::FunctionBuilder& builder) {
        if (name.empty() || descriptor.empty()) {
            throw std::runtime_error("Function name or function descriptor is empty");
        }

        moduleweb::AttributeBuilder attributeBuilder(builder);
        for (auto& attr : attributes) {
            attr->emit(attributeBuilder);
        }

        builder
            .modifiers(modifiers)
            .descriptor(name, descriptor)
            .build();
    }
}