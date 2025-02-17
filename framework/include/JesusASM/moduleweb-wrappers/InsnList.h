// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_INSNLIST_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_INSNLIST_H

#include "moduleweb/builder/insn_builder.h"
#include "moduleweb/builder/opcodes.h"

#include <string>

namespace moduleweb {
    template <class Builder>
    class AttributeBuilder;

    using Label = moduleweb_label;
    using Opcode = moduleweb_opcodes;

    class InsnList {
    public:
        InsnList();
        ~InsnList();

        void stackPush(i32 amount);
        void stackPop(i32 amount);

        Label* getLabel(std::string_view name) const;
        Label* getLabel(std::string& name) const;

        InsnList& insn(Opcode opcode);

        InsnList& callInsn(Opcode opcode, std::string_view module,
                       std::string_view name, std::string_view descriptor);
        InsnList& callInsn(Opcode opcode, std::string& module,
                       std::string& name, std::string& descriptor);

        InsnList& varInsn(Opcode opcode, u16 local);

        InsnList& byteInsn(Opcode opcode, i8 value);
        InsnList& shortInsn(Opcode opcode, i16 value);
        InsnList& intInsn(Opcode opcode, i32 value);
        InsnList& longInsn(Opcode opcode, i64 value);

        Label* createLabel(std::string_view name = "");
        Label* createLabel(std::string& name);

        InsnList& addLabel(Label* label);

    private:
        moduleweb_insn_list mList{};
    };
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_INSNLIST_H
