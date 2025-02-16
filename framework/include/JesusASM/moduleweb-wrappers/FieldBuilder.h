// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_FIELDBUILDER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_FIELDBUILDER_H 1

#include "JesusASM/moduleweb-wrappers/AttributeBuilder.h"

#include <string>

namespace moduleweb {
    class ClassBuilder;

    class FieldBuilder {
    friend class AttributeBuilder<FieldBuilder>;
    public:
        explicit FieldBuilder(ClassBuilder& clas);
        ~FieldBuilder();

        [[nodiscard]] moduleweb_module_builder* getModule() const;

        FieldBuilder& modifiers(u16 modifiers);

        FieldBuilder& descriptor(std::string_view name, std::string_view descriptor);
        FieldBuilder& descriptor(std::string& name, std::string& descriptor);

        void build();

    private:
        ClassBuilder& mClassBuilder;
        moduleweb_field_builder mModulewebBuilder{};
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_FIELDBUILDER_H
