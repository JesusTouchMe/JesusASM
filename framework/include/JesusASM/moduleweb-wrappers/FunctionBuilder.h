// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_FUNCTIONBUILDER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_FUNCTIONBUILDER_H 1

#include "JesusASM/moduleweb-wrappers/AttributeBuilder.h"

#include <string>

namespace moduleweb {
    class ModuleBuilder;

    class FunctionBuilder {
    friend class AttributeBuilder<FunctionBuilder>;
    public:
        explicit FunctionBuilder(ModuleBuilder& module);
        ~FunctionBuilder();

        [[nodiscard]] moduleweb_module_builder* getModule() const;

        FunctionBuilder& modifiers(u16 modifiers);

        FunctionBuilder& descriptor(std::string_view name, std::string_view descriptor);
        FunctionBuilder& descriptor(std::string& name, std::string& descriptor);

        void build();

    private:
        ModuleBuilder& mModuleBuilder;
        moduleweb_function_builder mModulewebBuilder{};
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_FUNCTIONBUILDER_H
