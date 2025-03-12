// Copyright 2025 JesusTouchMe

#include "JesusASM/Attributes.h"

namespace JesusASM {
    std::string_view RequiredPluginsAttribute::getName() const {
        return "RequiredPlugins";
    }

    u32 RequiredPluginsAttribute::getBufferSize() const {
        // u16 plugin_count
        // u16 plugins[plugin_count]
        return 2 + value.size() * 2;
    }

    void RequiredPluginsAttribute::writeTo(moduleweb_module_builder* module, moduleweb::OutStream& stream) const {
        if (value.size() > 0xFFFF) {
            throw std::runtime_error("Too many required plugins. Please split into two attributes.");
        }

        stream.writeU16(value.size());

        for (const auto& plugin : value) {
            stream.writeU16(moduleweb_module_builder_resolve_string(module, plugin.c_str()));
        }
    }
}
