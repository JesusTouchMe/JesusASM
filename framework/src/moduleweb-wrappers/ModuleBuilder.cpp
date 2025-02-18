// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/ModuleBuilder.h"
#include "JesusASM/moduleweb-wrappers/ModuleInfo.h"

namespace moduleweb {
    ModuleBuilder::ModuleBuilder() {
        mModulewebBuilder.constant_pool_index = 1;
    }

    ModuleBuilder::~ModuleBuilder() {
        moduleweb_module_builder_delete(&mModulewebBuilder);
    }

    moduleweb_module_builder* ModuleBuilder::getModule() {
        return &mModulewebBuilder;
    }

    ModuleBuilder& ModuleBuilder::version(u16 version) {
        moduleweb_module_builder_version(&mModulewebBuilder, version);
        return *this;
    }

    ModuleBuilder& ModuleBuilder::name(std::string_view name) {
        std::string temp(name);
        return this->name(temp);
    }

    ModuleBuilder& ModuleBuilder::name(std::string& name) {
        moduleweb_module_builder_name(&mModulewebBuilder, name.c_str());
        return *this;
    }

    void ModuleBuilder::build(ModuleInfo& info) {
        moduleweb_module_builder_build(&mModulewebBuilder, &info.mInfo);
    }
}