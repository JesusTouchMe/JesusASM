// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/ClassBuilder.h"

namespace moduleweb {
    MethodBuilder::MethodBuilder(ClassBuilder& clas)
        : mClassBuilder(clas) {
        mModulewebBuilder.module = clas.getModule();
    }

    MethodBuilder::~MethodBuilder() {
        moduleweb_method_builder_delete(&mModulewebBuilder);
    }

    moduleweb_module_builder* MethodBuilder::getModule() const {
        return mModulewebBuilder.module;
    }

    MethodBuilder& MethodBuilder::modifiers(u16 modifiers) {
        moduleweb_method_builder_modifiers(&mModulewebBuilder, modifiers);
        return *this;
    }

    MethodBuilder& MethodBuilder::descriptor(std::string_view name, std::string_view descriptor) {
        std::string tempName(name);
        std::string tempDesc(descriptor);

        return this->descriptor(tempName, tempDesc);
    }

    MethodBuilder& MethodBuilder::descriptor(std::string& name, std::string& descriptor) {
        moduleweb_method_builder_descriptor(&mModulewebBuilder, name.c_str(), descriptor.c_str());
        return *this;
    }

    MethodBuilder& MethodBuilder::function(std::string_view module, std::string_view name, std::string_view descriptor) {
        std::string tempModule(module);
        std::string tempName(name);
        std::string tempDesc(descriptor);

        return this->function(tempModule, tempName, tempDesc);
    }

    MethodBuilder& MethodBuilder::function(std::string& module, std::string& name, std::string& descriptor) {
        moduleweb_method_builder_function(&mModulewebBuilder, module.c_str(), name.c_str(), descriptor.c_str());
        return *this;
    }

    void MethodBuilder::build() {
        moduleweb_class_builder_add_method(&mClassBuilder.mModulewebBuilder, moduleweb_method_builder_build(&mModulewebBuilder));
    }
}
