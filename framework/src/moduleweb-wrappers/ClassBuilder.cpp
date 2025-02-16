// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/ClassBuilder.h"
#include "JesusASM/moduleweb-wrappers/ModuleBuilder.h"

namespace moduleweb {
    ClassBuilder::ClassBuilder(ModuleBuilder& module)
        : mModuleBuilder(module) {
        mModulewebBuilder.module = mModuleBuilder.getModule();
    }

    moduleweb_module_builder* ClassBuilder::getModule() const {
        return mModulewebBuilder.module;
    }

    ClassBuilder& ClassBuilder::modifiers(u16 modifiers) {
        moduleweb_class_builder_modifiers(&mModulewebBuilder, modifiers);
        return *this;
    }

    ClassBuilder& ClassBuilder::name(std::string_view name) {
        std::string temp(name);
        return this->name(temp);
    }

    ClassBuilder& ClassBuilder::name(std::string& name) {
        moduleweb_class_builder_name(&mModulewebBuilder, name.c_str());
        return *this;
    }

    ClassBuilder& ClassBuilder::super(std::string_view superModule, std::string_view superName) {
        std::string tempModule(superModule);
        std::string tempName(superName);

        return this->super(tempModule, tempName);
    }

    ClassBuilder& ClassBuilder::super(std::string& superModule, std::string& superName) {
        moduleweb_class_builder_super_class(&mModulewebBuilder, superModule.c_str(), superName.c_str());
        return *this;
    }

    void ClassBuilder::build() {
        moduleweb_module_builder_add_class(&mModuleBuilder.mModulewebBuilder, moduleweb_class_builder_build(&mModulewebBuilder));
    }
}