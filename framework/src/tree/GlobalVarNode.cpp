// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/AttributeBuilder.h"

#include "JesusASM/tree/GlobalVarNode.h"

#include <format>
#include <stdexcept>

namespace JesusASM::tree {
    GlobalVarNode::GlobalVarNode(u16 modifiers, std::string_view name, std::string_view descriptor)
        : modifiers(modifiers)
        , name(name)
        , descriptor(descriptor) {}

    GlobalVarNode::GlobalVarNode(u16 modifiers, std::string&& name, std::string&& descriptor)
        : modifiers(modifiers)
        , name(std::move(name))
        , descriptor(std::move(descriptor)) {}

    void GlobalVarNode::print(std::ostream& stream) const {
        stream << std::format("global {}:{}", name, descriptor);
    }

    void GlobalVarNode::emit(moduleweb::GlobalVarBuilder& builder) {
        if (name.empty() || descriptor.empty()) {
            throw std::runtime_error("Global var name or global var descriptor is empty");
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