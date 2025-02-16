// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/ClassNode.h"

namespace JesusASM::tree {
    ClassNode::ClassNode(u16 modifiers, std::string_view name, Name superClass)
        : modifiers(modifiers)
        , name(name)
        , superClass(std::move(superClass)) {}

    ClassNode::ClassNode(u16 modifiers, std::string&& name, Name&& superClass)
        : modifiers(modifiers)
        , name(std::move(name))
        , superClass(std::move(superClass)) {}

    void ClassNode::emit(moduleweb::ClassBuilder& builder) {
        if (name.empty()) {
            throw std::runtime_error("Class name is empty");
        }

        moduleweb::AttributeBuilder attributeBuilder(builder);
        for (auto& attr : attributes) {
            attr->emit(attributeBuilder);
        }

        moduleweb::FieldBuilder fieldBuilder(builder);
        for (auto& field : fields) {
            field->emit(fieldBuilder);
        }

        builder
            .modifiers(modifiers)
            .name(name);

        if (superClass) {
            builder.super(superClass.moduleName, superClass.name);
        }

        builder.build();
    }
}