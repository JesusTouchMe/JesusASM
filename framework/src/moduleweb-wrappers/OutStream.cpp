// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/OutStream.h"


namespace moduleweb {
    FileOutStream::FileOutStream(std::string_view name)
        : mFileName(name) {
         errorCheck(moduleweb_outstream_init(&mStream, mFileName.c_str()));
    }

    FileOutStream::~FileOutStream() {
        moduleweb_outstream_uninit(&mStream);
    }

    void FileOutStream::flush() {
        errorCheck(moduleweb_outstream_flush(&mStream));
    }

    void FileOutStream::writeU8(u8 value) {
        errorCheck(moduleweb_outstream_write_u8(&mStream, value));
    }

    void FileOutStream::writeU16(u16 value) {
        errorCheck(moduleweb_outstream_write_u16(&mStream, value));
    }

    void FileOutStream::writeU32(u32 value) {
        errorCheck(moduleweb_outstream_write_u32(&mStream, value));
    }

    void FileOutStream::writeU64(u64 value) {
        errorCheck(moduleweb_outstream_write_u64(&mStream, value));
    }

    void FileOutStream::writeBytes(const u8* data, u64 size) {
        errorCheck(moduleweb_outstream_write_bytes(&mStream, data, size));
    }

    MemoryOutStream::MemoryOutStream(u8* buffer, u64 bufferSize) {
        errorCheck(moduleweb_outstream_init_buffer(&mStream, buffer, bufferSize));
    }

    MemoryOutStream::~MemoryOutStream() {
        moduleweb_outstream_uninit_buffer(&mStream);
    }

    void MemoryOutStream::flush() {
        errorCheck(moduleweb_outstream_flush(&mStream));
    }

    void MemoryOutStream::writeU8(u8 value) {
        errorCheck(moduleweb_outstream_write_u8(&mStream, value));
    }

    void MemoryOutStream::writeU16(u16 value) {
        errorCheck(moduleweb_outstream_write_u16(&mStream, value));
    }

    void MemoryOutStream::writeU32(u32 value) {
        errorCheck(moduleweb_outstream_write_u32(&mStream, value));
    }

    void MemoryOutStream::writeU64(u64 value) {
        errorCheck(moduleweb_outstream_write_u64(&mStream, value));
    }

    void MemoryOutStream::writeBytes(const u8* data, u64 size) {
        errorCheck(moduleweb_outstream_write_bytes(&mStream, data, size));
    }

    ExpandingMemoryOutStream::ExpandingMemoryOutStream()
        : mBuffer(nullptr)
        , mCapacity(0) {
        errorCheck(moduleweb_outstream_init_buffer(&mStream, mBuffer, mCapacity));
    }

    ExpandingMemoryOutStream::~ExpandingMemoryOutStream() {
        delete[] mBuffer;

        moduleweb_outstream_uninit_buffer(&mStream);
    }

    const void* ExpandingMemoryOutStream::getContentBuffer(bool copy) const {
        if (copy) {
            u8* buffer = new u8[getContentSize()];
            std::memcpy(buffer, mBuffer, getContentSize());

            return buffer;
        } else {
            return mBuffer;
        }
    }

    u64 ExpandingMemoryOutStream::getContentSize() const {
        return mStream.memory.pos;
    }

    void ExpandingMemoryOutStream::flush() {
        errorCheck(moduleweb_outstream_flush(&mStream));
    }

    void ExpandingMemoryOutStream::writeU8(u8 value) {
        checkCapacity(1);
        errorCheck(moduleweb_outstream_write_u8(&mStream, value));
    }

    void ExpandingMemoryOutStream::writeU16(u16 value) {
        checkCapacity(2);
        errorCheck(moduleweb_outstream_write_u16(&mStream, value));
    }

    void ExpandingMemoryOutStream::writeU32(u32 value) {
        checkCapacity(4);
        errorCheck(moduleweb_outstream_write_u32(&mStream, value));
    }

    void ExpandingMemoryOutStream::writeU64(u64 value) {
        checkCapacity(8);
        errorCheck(moduleweb_outstream_write_u64(&mStream, value));
    }

    void ExpandingMemoryOutStream::writeBytes(const u8* data, u64 size) {
        checkCapacity(size);
        errorCheck(moduleweb_outstream_write_bytes(&mStream, data, size));
    }

    void ExpandingMemoryOutStream::checkCapacity(u64 amount) {
        if (mStream.memory.pos + amount >= mCapacity) {
            if (mCapacity == 0) {
                mCapacity = 128; // a nice size to start off with
                mBuffer = new u8[mCapacity];
            } else {
                u64 newCapacity = mCapacity * 2;
                u8* newBuffer = new u8[newCapacity];

                std::memcpy(newBuffer, mBuffer, mCapacity);

                delete[] mBuffer;
                mBuffer = newBuffer;
                mCapacity = newCapacity;
            }

            errorCheck(moduleweb_outstream_reopen_buffer(&mStream, mBuffer, mCapacity));
        }
    }
}
