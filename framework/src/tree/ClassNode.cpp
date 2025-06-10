// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/ClassNode.h"

#include <format>

namespace JesusASM::tree {
    ClassNode::ClassNode(u16 modifiers, std::string_view name, Name superClass)
        : modifiers(modifiers)
        , name(name)
        , superClass(std::move(superClass)) {}

    ClassNode::ClassNode(u16 modifiers, std::string&& name, Name&& superClass)
        : modifiers(modifiers)
        , name(std::move(name))
        , superClass(std::move(superClass)) {}

    void ClassNode::print(std::ostream& stream) const {
        stream << std::format("class {} ", name);

        if (!superClass.name.empty()) {
            stream << "extends ";
            if (!superClass.moduleName.empty()) stream << std::format("{}:", superClass.moduleName);
            stream << std::format("{} ", superClass.name);
        }

        stream << "{\n";

        for (const auto& field : fields) {
            stream << "    ";
            field->print(stream);
            stream << "\n";
        }

        stream << "}";
    }

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

        moduleweb::MethodBuilder methodBuilder(builder);
        for (auto& method : methods) {
            method->emit(methodBuilder);
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