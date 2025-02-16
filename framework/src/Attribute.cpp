// Copyright 2025 JesusTouchMe

#include "JesusASM/Attribute.h"

namespace JesusASM {
    Attribute::Attribute(std::string_view name, const void* info, u32 size)
        : mName(name)
        , mSize(size) {
        mInfo = new u8[mSize];
        std::memcpy(mInfo, info, size);
    }

    Attribute::~Attribute() {
        delete[] mInfo;
    }

    std::string_view Attribute::getName() const {
        return mName;
    }

    const u8* Attribute::getInfo() const {
        return mInfo;
    }

    u32 Attribute::getSize() const {
        return mSize;
    }
}