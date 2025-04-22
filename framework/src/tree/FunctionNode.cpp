// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/FunctionNode.h"

#include <format>
#include <stdexcept>

namespace JesusASM::tree {

    FunctionNode::FunctionNode(u16 modifiers, std::string_view name, std::string_view descriptor)
        : modifiers(modifiers)
        , name(name)
        , descriptor(descriptor) {}

    FunctionNode::FunctionNode(u16 modifiers, std::string&& name, std::string&& descriptor)
        : modifiers(modifiers)
        , name(std::move(name))
        , descriptor(std::move(descriptor)) {}

    void FunctionNode::print(std::ostream& stream) const {
        stream << std::format("function {}:{} {{\n", name, descriptor);
        instructions.print(stream);
        stream << "}";
    }

    void FunctionNode::emit(moduleweb::FunctionBuilder& builder) {
        if (name.empty() || descriptor.empty()) {
            throw std::runtime_error("Function name or function descriptor is empty");
        }

        moduleweb::AttributeBuilder attributeBuilder(builder);
        for (auto& attr : attributes) {
            attr->emit(attributeBuilder);
        }

        if (!(modifiers & MODULEWEB_FUNCTION_MODIFIER_NATIVE)) {
            moduleweb::InsnList insnBuilder(builder.getModule());

            int arguments = 0;

            size_t i = 1;
            while (i < descriptor.size() && descriptor[i] != ')') {
                char c = descriptor[i];

                switch (c) {
                    case 'B':
                    case 'S':
                    case 'I':
                    case 'C':
                    case 'Z':
                    case 'F':
                        arguments += 1;
                        i++;
                        break;

                    case 'L':
                    case 'D':
                        arguments += 2;
                        i++;
                        break;

                    case 'R': {
                        size_t semicolon = descriptor.find(';', i);
                        if (semicolon == std::string_view::npos) {
                            throw std::invalid_argument("Unterminated object type in descriptor");
                        }

                        arguments += 2;
                        i = semicolon + 1;

                        break;
                    }

                    case '[': {
                        while (descriptor[i] == '[')
                            i++;

                        if (descriptor[i] == 'R') {
                            size_t semicolon = descriptor.find(';', i);
                            if (semicolon == std::string_view::npos)
                                throw std::invalid_argument("Unterminated array object type in descriptor");
                            i = semicolon + 1;
                        } else {
                            i++;
                        }
                        arguments += 2;

                        break;
                    }

                    default:
                        throw std::invalid_argument(std::string("Unexpected character in descriptor: ") + c);
                }
            }

            insnBuilder.setLocalIndex(arguments);
            
            instructions.emit(insnBuilder);
            insnBuilder.build(attributeBuilder);
        }

        builder
            .modifiers(modifiers)
            .descriptor(name, descriptor)
            .build();
    }
}