// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/GlobalVarBuilder.h"
#include "JesusASM/moduleweb-wrappers/ModuleBuilder.h"

namespace moduleweb {

    GlobalVarBuilder::GlobalVarBuilder(ModuleBuilder& module)
        : mModuleBuilder(module) {
        mModulewebBuilder.module = mModuleBuilder.getModule();
    }

    GlobalVarBuilder::~GlobalVarBuilder() {
        moduleweb_global_var_builder_delete(&mModulewebBuilder);
    }

    moduleweb_module_builder* GlobalVarBuilder::getModule() const {
        return mModulewebBuilder.module;
    }

    GlobalVarBuilder& GlobalVarBuilder::modifiers(u16 modifiers) {
        moduleweb_global_var_builder_modifiers(&mModulewebBuilder, modifiers);
        return *this;
    }

    GlobalVarBuilder& GlobalVarBuilder::descriptor(std::string_view name, std::string_view descriptor) {
        std::string tempName(name);
        std::string tempDesc(descriptor);

        return this->descriptor(tempName, tempDesc);
    }

    GlobalVarBuilder& GlobalVarBuilder::descriptor(std::string& name, std::string& descriptor) {
        moduleweb_global_var_builder_descriptor(&mModulewebBuilder, name.c_str(), descriptor.c_str());
        return *this;
    }

    void GlobalVarBuilder::build() {
        moduleweb_module_builder_add_global_var(mModulewebBuilder.module, moduleweb_global_var_builder_build(&mModulewebBuilder));
    }
}