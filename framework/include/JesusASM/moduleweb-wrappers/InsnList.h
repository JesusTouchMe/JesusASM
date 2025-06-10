// Copyright 2025 JesusTouchMe

#ifndef JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_INSNLIST_H
#define JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_INSNLIST_H

#include "JesusASM/Opcodes.h"

#include "JesusASM/moduleweb-wrappers/AttributeBuilder.h"

#include "moduleweb/builder/insn_builder.h"

#include <string>

namespace moduleweb {
    using Label = moduleweb_label;
    using Opcode = JesusASM::Opcode;

    class InsnList {
    public:
        explicit InsnList(moduleweb_module_builder* module);
        ~InsnList();

        void setStackDepth(i32 depth);
        void setLocalIndex(u16 index);

        Label* getLabel(std::string_view name) const;
        Label* getLabel(std::string& name) const;

        Label* createLabel(std::string_view name = "");
        Label* createLabel(std::string& name);

        InsnList& addLabel(Label* label);

        InsnList& insn(Opcode opcode);

        InsnList& callInsn(Opcode opcode, std::string_view module,
                           std::string_view name, std::string_view descriptor);
        InsnList& callInsn(Opcode opcode, std::string& module,
                           std::string& name, std::string& descriptor);

        InsnList& jumpInsn(Opcode opcode, Label* label);

        InsnList& classInsn(Opcode opcode, std::string_view module, std::string_view name);
        InsnList& classInsn(Opcode opcode, std::string& module, std::string& name);

        InsnList& fieldInsn(Opcode opcode, std::string_view ownerModule, std::string_view owner,
                            std::string_view name, std::string_view descriptor);
        InsnList& fieldInsn(Opcode opcode, std::string& ownerModule, std::string& owner,
                            std::string& name, std::string& descriptor);

        InsnList& methodInsn(Opcode opcode, std::string& ownerModule, std::string& owner,
                             std::string& name, std::string& descriptor);

        InsnList& globalVarInsn(Opcode opcode, std::string_view module,
                                std::string_view name, std::string_view descriptor);

        InsnList& globalVarInsn(Opcode opcode, std::string& module,
                                std::string& name, std::string& descriptor);

        InsnList& ldcInsn(std::string_view value);
        InsnList& ldcInsn(std::string& value);

        InsnList& varInsn(Opcode opcode, u16 local);

        InsnList& byteInsn(Opcode opcode, i8 value);
        InsnList& shortInsn(Opcode opcode, i16 value);
        InsnList& intInsn(Opcode opcode, i32 value);
        InsnList& longInsn(Opcode opcode, i64 value);

        template<class Builder>
        void build(AttributeBuilder<Builder>& builder);

    private:
        moduleweb_insn_list mList{};
        i32 mStackDepth = 0;
    };

    template<class Builder>
    void InsnList::build(AttributeBuilder<Builder>& builder) {
        moduleweb_attribute_builder_code(&builder.mModulewebBuilder, &mList);
        builder.build();
    }
}

#endif //JESUSASM_FRAMEWORK_INCLUDE_JESUSASM_MODULEWEB_WRAPPERS_INSNLIST_H
