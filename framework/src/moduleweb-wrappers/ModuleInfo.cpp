// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/ModuleInfo.h"

namespace moduleweb {
    ModuleInfo::~ModuleInfo() {
        moduleweb_module_info_uninit(&mInfo);
    }

    void ModuleInfo::print() {
        moduleweb_module_info_print(&mInfo, 0);
    }

    void ModuleInfo::emit(OutStream& stream) {
        moduleweb_module_info_emit_bytes(&mInfo, stream.getStream());
    }
}