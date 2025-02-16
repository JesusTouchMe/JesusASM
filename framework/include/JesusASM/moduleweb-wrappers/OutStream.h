// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_OUTSTREAM_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_OUTSTREAM_H 1

#include "moduleweb/stream.h"

#include <iostream>
#include <string>

namespace moduleweb {
    class OutStream {
    public:
        virtual ~OutStream() = default;

        [[nodiscard]] moduleweb_outstream* getStream() { return &mStream; }

        virtual void flush() = 0;

        virtual void writeU8(u8 value) = 0;
        virtual void writeU16(u16 value) = 0;
        virtual void writeU32(u32 value) = 0;
        virtual void writeU64(u64 value) = 0;
        virtual void writeBytes(const u8* data, u64 size) = 0;

        void writeString(std::string_view string) {
            writeBytes(reinterpret_cast<const u8*>(string.data()), string.length());
        }

    protected:
        moduleweb_outstream mStream;

        constexpr void errorCheck(int ret) {
            if (ret) {
                std::cout << "error: " << moduleweb_outstream_strerror(&mStream) << "\n";
                std::exit(1);
            }
        }
    };

    class FileOutStream : public OutStream {
    public:
        explicit FileOutStream(std::string_view name);
        ~FileOutStream() override;

        void flush() override;

        void writeU8(u8 value) override;
        void writeU16(u16 value) override;
        void writeU32(u32 value) override;
        void writeU64(u64 value) override;
        void writeBytes(const u8* data, u64 size) override;

    private:
        std::string mFileName;
    };

    class MemoryOutStream : public OutStream {
    public:
        MemoryOutStream(u8* buffer, u64 bufferSize);
        ~MemoryOutStream() override;

        void flush() override;

        void writeU8(u8 value) override;
        void writeU16(u16 value) override;
        void writeU32(u32 value) override;
        void writeU64(u64 value) override;
        void writeBytes(const u8* data, u64 size) override;
    };

    class ExpandingMemoryOutStream : public OutStream {
    public:
        ExpandingMemoryOutStream();
        ~ExpandingMemoryOutStream() override;

        void flush() override;

        void writeU8(u8 value) override;
        void writeU16(u16 value) override;
        void writeU32(u32 value) override;
        void writeU64(u64 value) override;
        void writeBytes(const u8* data, u64 size) override;

    private:
        u8* mBuffer;
        u64 mCapacity;

        void checkCapacity(u64 amount);
    };
}

#endif // JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_OUTSTREAM_H
