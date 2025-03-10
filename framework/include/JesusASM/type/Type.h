// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TYPE_TYPE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TYPE_TYPE_H

#include <string>
#include <vector>

namespace JesusASM {
    class Type {
    public:
        Type(std::string_view name, std::string_view descriptor);

        std::string_view getName() const;
        std::string_view getDescriptor() const;

        static void Init();
        static Type* GetBuiltinType(std::string_view name);
        static Type* GetClassType(std::string_view moduleName, std::string_view className);
        static Type* GetFunctionType(Type* returnType, const std::vector<Type*>& argTypes);

    private:
        std::string mName;
        std::string mDescriptor;
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_TYPE_TYPE_H
