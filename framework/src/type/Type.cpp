// Copyright 2025 JesusTouchMe

#include "JesusASM/type/Type.h"

#include <memory>
#include <vector>

namespace JesusASM {
    Type::Type(std::string_view name, std::string_view descriptor)
        : mName(name)
        , mDescriptor(descriptor) {}

    std::string_view Type::getName() const {
        return mName;
    }

    std::string_view Type::getDescriptor() const {
        return mDescriptor;
    }

    static std::vector<std::unique_ptr<Type>> types;

    void Type::Init() {
        types.push_back(std::make_unique<Type>("void", "V"));
        types.push_back(std::make_unique<Type>("bool", "Z"));
        types.push_back(std::make_unique<Type>("char", "C"));
        types.push_back(std::make_unique<Type>("byte", "B"));
        types.push_back(std::make_unique<Type>("short", "S"));
        types.push_back(std::make_unique<Type>("int", "I"));
        types.push_back(std::make_unique<Type>("long", "L"));
        types.push_back(std::make_unique<Type>("float", "F"));
        types.push_back(std::make_unique<Type>("double", "D"));
        types.push_back(std::make_unique<Type>("handle", "H"));
    }

    Type* Type::GetBuiltinType(std::string_view name) {
        auto it = std::find_if(types.begin(), types.end(), [name](auto& type) {
            return type->getName() == name;
        });

        if (it != types.end()) {
            return it->get();
        }

        return nullptr;
    }

    Type* Type::GetClassType(std::string_view moduleName, std::string_view className) {
        std::string qualifiedName(moduleName);
        qualifiedName += ':';
        qualifiedName += className;

        auto it = std::find_if(types.begin(), types.end(), [&qualifiedName](auto& type) {
            return type->getName() == qualifiedName;
        });

        if (it != types.end()) {
            return it->get();
        }

        std::string descriptor = "R";
        descriptor += qualifiedName;
        descriptor += ";";

        types.push_back(std::make_unique<Type>(qualifiedName, descriptor));

        return types.back().get();
    }

    Type* Type::GetFunctionType(Type* returnType, const std::vector<Type*>& argTypes) {
        std::string descriptor = "(";

        for (const auto* arg : argTypes) {
            descriptor += arg->mDescriptor;
        }

        descriptor += ')';

        descriptor += returnType->mDescriptor;

        auto it = std::find_if(types.begin(), types.end(), [&descriptor](auto& type) {
            return type->getName() == descriptor;
        });

        if (it != types.end()) {
            return it->get();
        }

        std::string name = returnType->mName;

        name += '(';
        for (const auto* arg : argTypes) {
            name += arg->mName;
        }
        name += ')';

        types.push_back(std::make_unique<Type>(name, descriptor));

        return types.back().get();
    }
}