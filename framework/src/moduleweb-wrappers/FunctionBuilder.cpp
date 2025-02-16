// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/FunctionBuilder.h"
#include "JesusASM/moduleweb-wrappers/ModuleBuilder.h"

namespace moduleweb {
    FunctionBuilder::FunctionBuilder(ModuleBuilder& module)
        : mModuleBuilder(module) {
        mModulewebBuilder.module = mModuleBuilder.getModule();
    }

    FunctionBuilder::~FunctionBuilder() {
        moduleweb_function_builder_delete(&mModulewebBuilder);
    }

    moduleweb_module_builder* FunctionBuilder::getModule() const {
        return mModulewebBuilder.module;
    }

    FunctionBuilder& FunctionBuilder::modifiers(u16 modifiers) {
        moduleweb_function_builder_modifiers(&mModulewebBuilder, modifiers);
        return *this;
    }

    FunctionBuilder& FunctionBuilder::descriptor(std::string_view name, std::string_view descriptor) {
        std::string tempName(name);
        std::string tempDesc(descriptor);

        return this->descriptor(tempName, tempDesc);
    }

    FunctionBuilder& FunctionBuilder::descriptor(std::string& name, std::string& descriptor) {
        moduleweb_function_builder_descriptor(&mModulewebBuilder, name.c_str(), descriptor.c_str());
        return *this;
    }

    void FunctionBuilder::build() {
        moduleweb_module_builder_add_function(&mModuleBuilder.mModulewebBuilder, moduleweb_function_builder_build(&mModulewebBuilder));
    }
}