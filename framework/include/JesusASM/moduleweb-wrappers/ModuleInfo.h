// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_MODULEINFO_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_MODULEINFO_H 1

#include "JesusASM/moduleweb-wrappers/OutStream.h"

#include "moduleweb/module_info.h"

#include <string>

namespace moduleweb {
    class ModuleBuilder;

    class ModuleInfo {
    friend class ModuleBuilder;
    public:
        ~ModuleInfo();

        void print();

        void emit(OutStream& stream);

    private:
        moduleweb_module_info mInfo{};
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_MODULEINFO_H
