// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_MODULEBUILDER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_MODULEBUILDER_H 1

#include "JesusASM/moduleweb-wrappers/ClassBuilder.h"
#include "JesusASM/moduleweb-wrappers/FunctionBuilder.h"
#include "JesusASM/moduleweb-wrappers/ModuleInfo.h"

namespace moduleweb {
    class ModuleBuilder {
    friend class AttributeBuilder<ModuleBuilder>;
    friend class ClassBuilder;
    friend class FunctionBuilder;
    public:
        ModuleBuilder();
        ~ModuleBuilder();

        [[nodiscard]] moduleweb_module_builder* getModule();

        ModuleBuilder& version(u16 version);

        ModuleBuilder& name(std::string_view name);
        ModuleBuilder& name(std::string& name);

        void build(ModuleInfo& info);

    private:
        moduleweb_module_builder mModulewebBuilder{};
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_MODULEBUILDER_H
