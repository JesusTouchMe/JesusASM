// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_NAME_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_NAME_H 1

#include <stdexcept>
#include <string>

namespace JesusASM {
    /**
     * A "nullable" struct that will hold the qualified name of an item in a module (e.g. a class or function).
     * Nullability is implemented with std::nullptr_t constructor and operator==
     */
    struct Name {
        std::string moduleName;
        std::string name;

        constexpr Name() = default;

        constexpr Name(std::nullptr_t) {}

        template <std::size_t N>
        constexpr Name(const char (&qualifiedName)[N]) : Name(std::string_view(qualifiedName, N - 1)) {}

        constexpr Name(std::string_view qualifiedName) {
            auto pos = qualifiedName.rfind(':');
            if (pos != std::string_view::npos) {
                moduleName = qualifiedName.substr(0, pos);
                name = qualifiedName.substr(pos + 1);
            } else {
                throw std::invalid_argument("Invalid qualified name format");
            }
        }

        constexpr Name(std::string_view moduleName, std::string_view name) : moduleName(moduleName), name(name) {}
        constexpr Name(std::string&& moduleName, std::string&& name) : moduleName(std::move(moduleName)), name(std::move(name)) {}

        constexpr Name& operator=(std::string_view qualifiedName) {
            auto pos = qualifiedName.rfind(':');
            if (pos != std::string_view::npos) {
                moduleName = qualifiedName.substr(0, pos);
                name = qualifiedName.substr(pos + 1);
            } else {
                throw std::invalid_argument("Invalid qualified name format");
            }

            return *this;
        }

        [[nodiscard]] constexpr bool hasValue() const noexcept {
            return !moduleName.empty() && !name.empty();
        }

        constexpr bool operator==(std::nullptr_t) const noexcept { return hasValue(); }

        constexpr bool operator==(const Name& other) const noexcept {
            return moduleName == other.moduleName && name == other.name;
        }

        constexpr operator bool() const noexcept {
            return hasValue();
        }
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_NAME_H
