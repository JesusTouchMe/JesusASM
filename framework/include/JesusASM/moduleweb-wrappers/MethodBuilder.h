// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_METHODBUILDER_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_METHODBUILDER_H 1

#include "JesusASM/moduleweb-wrappers/AttributeBuilder.h"

#include <string>

namespace moduleweb {
    class ClassBuilder;

    class MethodBuilder {
    friend class AttributeBuilder<MethodBuilder>;
    public:
        explicit MethodBuilder(ClassBuilder& clas);
        ~MethodBuilder();

        [[nodiscard]] moduleweb_module_builder* getModule() const;

        MethodBuilder& modifiers(u16 modifiers);

        MethodBuilder& descriptor(std::string_view name, std::string_view descriptor);
        MethodBuilder& descriptor(std::string& name, std::string& descriptor);

        MethodBuilder& function(std::string_view module, std::string_view name, std::string_view descriptor);
        MethodBuilder& function(std::string& module, std::string& name, std::string& descriptor);

        void build();

    private:
        ClassBuilder& mClassBuilder;
        moduleweb_method_builder mModulewebBuilder{};
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_METHODBUILDER_H