// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_ATTRIBUTE_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_ATTRIBUTE_H 1

#include "JesusASM/moduleweb-wrappers/ModuleBuilder.h"
#include "JesusASM/moduleweb-wrappers/OutStream.h"

#include <stdexcept>
#include <string>
#include <type_traits>

namespace JesusASM {
    template <typename T>
    concept HasGetName = requires(T t) {
        { t.getName() } -> std::same_as<std::string_view>;
    };

    template <typename T>
    concept HasGetBufferSize = requires(T t) {
        { t.getBufferSize() } -> std::same_as<u32>;
    };

    template <typename T>
    concept HasWriteTo = requires(T t, moduleweb_module_builder* module, moduleweb::OutStream& stream) {
        { t.writeTo(module, stream) } -> std::same_as<void>;
    };

    class IAttribute {
    public:
        virtual ~IAttribute() = default;
        virtual std::string_view getName() const = 0;

        // TODO: find a better way to do this (i miss when i could just do template<class B>)
        virtual void emit(moduleweb::AttributeBuilder<moduleweb::ModuleBuilder>& builder) = 0;
        virtual void emit(moduleweb::AttributeBuilder<moduleweb::ClassBuilder>& builder) = 0;
        virtual void emit(moduleweb::AttributeBuilder<moduleweb::FieldBuilder>& builder) = 0;
        virtual void emit(moduleweb::AttributeBuilder<moduleweb::FunctionBuilder>& builder) = 0;
    };

    // Dirty template code. Reader discretion is advised

    template<class T>
    class Attribute : public IAttribute {
    public:
        Attribute(std::string_view name, T& value) requires HasWriteTo<T>
            : mName(name)
            , mValue(value) {}

        explicit Attribute(T& value) requires HasWriteTo<T> && HasGetName<T>
            : Attribute(value.getName(), value) {}

        std::string_view getName() const override {
            return mName;
        }

        const T& getValue() const {
            return mValue;
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::ModuleBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::ClassBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::FieldBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::FunctionBuilder>& builder) override {
            emitT(builder);
        }

    private:
        std::string mName;
        T mValue;

        template<class B>
        void emitT(moduleweb::AttributeBuilder<B>& builder) {
            if (mName.empty()) {
                throw std::runtime_error("Attribute name is empty");
            }

            const u8* info;
            u32 size;

            if constexpr (HasGetBufferSize<T>) {
                size = mValue.getBufferSize();
                u8* mutableInfo = new u8[size];

                moduleweb::MemoryOutStream stream(mutableInfo, size);
                mValue.writeTo(builder.getModule(), stream);

                info = mutableInfo;
            } else {
                moduleweb::ExpandingMemoryOutStream stream;
                mValue.writeTo(builder.getModule(), stream);

                info = static_cast<const u8*>(stream.getContentBuffer(true));
                size = stream.getContentSize();
            }

            builder
                .name(mName)
                .info(info, size)
                .build();

            delete[] info;
        }
    };

    template<>
    class Attribute<bool> : public IAttribute {
    public:
        explicit Attribute(std::string_view name, bool value)
                : mName(name)
                , mValue(value) {}

        std::string_view getName() const override {
            return mName;
        }

        bool getValue() const {
            return mValue;
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::ModuleBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::ClassBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::FieldBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::FunctionBuilder>& builder) override {
            emitT(builder);
        }

    private:
        std::string mName;
        bool mValue;

        template<class B>
        void emitT(moduleweb::AttributeBuilder<B>& builder) {
            if (mName.empty()) {
                throw std::runtime_error("Attribute name is empty");
            }

            const u8* info = reinterpret_cast<const u8*>(&mValue);
            u32 size = sizeof(mValue);

            builder
                .name(mName)
                .info(info, size)
                .build();
        }
    };

    template<class T>
    class Attribute<T*> : public IAttribute {
    public:
        explicit Attribute(std::string_view name, T* value, u32 size)
                : mName(name)
                , mValue(value)
                , mSize(size) {}

        std::string_view getName() const override {
            return mName;
        }

        T* getValue() const {
            return mValue;
        }

        u32 getSize() const {
            return mSize;
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::ModuleBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::ClassBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::FieldBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::FunctionBuilder>& builder) override {
            emitT(builder);
        }

    private:
        std::string mName;
        T* mValue;
        u32 mSize;

        template<class B>
        void emitT(moduleweb::AttributeBuilder<B>& builder) {
            if (mName.empty()) {
                throw std::runtime_error("Attribute name is empty");
            }

            builder
                    .name(mName)
                    .info(mValue, mSize)
                    .build();
        }
    };

    template<>
    class Attribute<std::string_view> : public IAttribute {
    public:
        explicit Attribute(std::string_view name, std::string_view value)
                : mName(name), mValue(value) {}

        std::string_view getName() const override {
            return mName;
        }

        std::string getValue() const {
            return mValue;
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::ModuleBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::ClassBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::FieldBuilder>& builder) override {
            emitT(builder);
        }

        void emit(moduleweb::AttributeBuilder<moduleweb::FunctionBuilder>& builder) override {
            emitT(builder);
        }

    private:
        std::string mName;
        std::string mValue;

        template<class B>
        void emitT(moduleweb::AttributeBuilder<B>& builder) {
            if (mName.empty()) {
                throw std::runtime_error("Attribute name is empty");
            }

            const u8* info = reinterpret_cast<const u8*>(mValue.data());
            u32 size = mValue.length();

            builder
                .name(mName)
                .info(info, size)
                .build();
        }
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_ATTRIBUTE_H
