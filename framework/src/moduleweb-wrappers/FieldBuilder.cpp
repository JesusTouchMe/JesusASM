// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/ClassBuilder.h"

namespace moduleweb {
    FieldBuilder::FieldBuilder(ClassBuilder& clas)
        : mClassBuilder(clas) {
        mModulewebBuilder.module = clas.getModule();
    }

    FieldBuilder::~FieldBuilder() {
        moduleweb_field_builder_delete(&mModulewebBuilder);
    }

    moduleweb_module_builder* FieldBuilder::getModule() const {
        return mModulewebBuilder.module;
    }

    FieldBuilder& FieldBuilder::modifiers(u16 modifiers) {
        moduleweb_field_builder_modifiers(&mModulewebBuilder, modifiers);
        return *this;
    }

    FieldBuilder& FieldBuilder::descriptor(std::string_view name, std::string_view descriptor) {
        std::string tempName(name);
        std::string tempDesc(descriptor);

        return this->descriptor(tempName, tempDesc);
    }

    FieldBuilder& FieldBuilder::descriptor(std::string& name, std::string& descriptor) {
        moduleweb_field_builder_descriptor(&mModulewebBuilder, name.c_str(), descriptor.c_str());
        return *this;
    }

    void FieldBuilder::build() {
        moduleweb_class_builder_add_field(&mClassBuilder.mModulewebBuilder, moduleweb_field_builder_build(&mModulewebBuilder));
    }
}