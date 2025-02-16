// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_CLASSBUILDER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_CLASSBUILDER_H 1

#include "JesusASM/moduleweb-wrappers/FieldBuilder.h"

namespace moduleweb {
    class ModuleBuilder;

    class ClassBuilder {
    friend class AttributeBuilder<ClassBuilder>;
    friend class FieldBuilder;
    public:
        explicit ClassBuilder(ModuleBuilder& module);

        [[nodiscard]] moduleweb_module_builder* getModule() const;

        ClassBuilder& modifiers(u16 modifiers);

        ClassBuilder& name(std::string_view name);
        ClassBuilder& name(std::string& name);

        ClassBuilder& super(std::string_view superModule, std::string_view superName);
        ClassBuilder& super(std::string& superModule, std::string& superName);

        void build();

    private:
        ModuleBuilder& mModuleBuilder;
        moduleweb_class_builder mModulewebBuilder{};
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_CLASSBUILDER_H
