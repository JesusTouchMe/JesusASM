// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_ATTRIBUTEBUILDER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_ATTRIBUTEBUILDER_H 1

#include "moduleweb/builder/module_builder.h"

#include <string>

namespace moduleweb {
    template <class Builder>
    class AttributeBuilder {
    public:
        explicit AttributeBuilder(Builder& builder)
            : mBuilder(builder) {
            mModulewebBuilder.module = mBuilder.getModule();
        }

        ~AttributeBuilder() {
            moduleweb_attribute_builder_delete(&mModulewebBuilder);
        }

        [[nodiscard]] moduleweb_module_builder* getModule() const {
            return mModulewebBuilder.module;
        }

        AttributeBuilder<Builder>& name(std::string_view name) {
            std::string temp(name);
            return this->name(temp);
        }

        AttributeBuilder<Builder>& name(std::string& name) {
            moduleweb_attribute_builder_name(&mModulewebBuilder, name.c_str());

            return *this;
        }

        AttributeBuilder<Builder>& info(const void* info, u32 length) {
            moduleweb_attribute_builder_info(&mModulewebBuilder, info, length);
            return *this;
        }

        void build() {
            moduleweb_attribute_vector_add(&mBuilder.mModulewebBuilder.attributes, moduleweb_attribute_builder_build(&mModulewebBuilder));
        }

    private:
        Builder& mBuilder;
        moduleweb_attribute_builder mModulewebBuilder{};
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_ATTRIBUTEBUILDER_H
