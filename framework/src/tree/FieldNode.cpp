// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/AttributeBuilder.h"

#include "JesusASM/tree/FieldNode.h"

#include <format>
#include <stdexcept>

namespace JesusASM::tree {
    FieldNode::FieldNode(u16 modifiers, std::string_view name, std::string_view descriptor)
        : modifiers(modifiers)
        , name(name)
        , descriptor(descriptor) {}

    FieldNode::FieldNode(u16 modifiers, std::string&& name, std::string&& descriptor)
        : modifiers(modifiers)
        , name(std::move(name))
        , descriptor(std::move(descriptor)) {}

    void FieldNode::print(std::ostream& stream) const {
        stream << std::format("field {}:{}", name, descriptor);
    }

    void FieldNode::emit(moduleweb::FieldBuilder& builder) {
        if (name.empty() || descriptor.empty()) {
            throw std::runtime_error("Field name or field descriptor is empty");
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