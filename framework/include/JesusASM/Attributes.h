// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_ATTRIBUTES_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_ATTRIBUTES_H

#include "JesusASM/moduleweb-wrappers/OutStream.h"

#include "moduleweb/builder/module_builder.h"

#include <string>
#include <vector>

namespace JesusASM {
    struct RequiredPluginsAttribute {
        std::vector<std::string> value;

        std::string_view getName() const;
        u32 getBufferSize() const;
        void writeTo(moduleweb_module_builder* module, moduleweb::OutStream& stream) const;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_ATTRIBUTES_H
