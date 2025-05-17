// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_GLOBALVARBUILDER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_GLOBALVARBUILDER_H

#include "JesusASM/moduleweb-wrappers/AttributeBuilder.h"

#include <string>

namespace moduleweb {
    class ModuleBuilder;

    class GlobalVarBuilder {
    friend class AttributeBuilder<GlobalVarBuilder>;
    public:
        explicit GlobalVarBuilder(ModuleBuilder& module);
        ~GlobalVarBuilder();

        [[nodiscard]] moduleweb_module_builder* getModule() const;

        GlobalVarBuilder& modifiers(u16 modifiers);

        GlobalVarBuilder& descriptor(std::string_view name, std::string_view descriptor);
        GlobalVarBuilder& descriptor(std::string& name, std::string& descriptor);

        void build();

    private:
        ModuleBuilder& mModuleBuilder;
        moduleweb_global_var_builder mModulewebBuilder{};
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_GLOBALVARBUILDER_H
