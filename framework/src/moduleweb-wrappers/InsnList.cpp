// Copyright 2025 JesusTouchMe

#include "JesusASM/moduleweb-wrappers/InsnList.h"

namespace moduleweb {
    InsnList::InsnList() {
        moduleweb_insn_list_init(&mList);
    }

    InsnList::~InsnList() {
        moduleweb_insn_list_uninit(&mList);
    }

    void InsnList::stackPush(i32 amount) {
        mList.stack_depth += amount;
    }

    void InsnList::stackPop(i32 amount) {
        mList.stack_depth -= amount;
    }

    Label* InsnList::getLabel(std::string_view name) const {
        std::string temp(name);
        return getLabel(temp);
    }

    Label* InsnList::getLabel(std::string& name) const {
        return moduleweb_insn_list_get_label(&mList, name.c_str());
    }

    InsnList& InsnList::insn(Opcode opcode) {
        moduleweb_insn_list_insn(&mList, opcode);
        return *this;
    }

    InsnList& InsnList::callInsn(Opcode opcode, std::string_view module, std::string_view name,
                                            std::string_view descriptor) {
        std::string tempModule(module);
        std::string tempName(name);
        std::string tempDesc(descriptor);

        return callInsn(opcode, tempModule, tempName, tempDesc);
    }

    InsnList& InsnList::callInsn(Opcode opcode, std::string& module, std::string& name, std::string& descriptor) {
        moduleweb_insn_list_call(&mList, opcode, module.c_str(), name.c_str(), descriptor.c_str());
        return *this;
    }

    InsnList& InsnList::varInsn(Opcode opcode, u16 local) {
        moduleweb_insn_list_var(&mList, opcode, local);
        return *this;
    }

    InsnList& InsnList::byteInsn(Opcode opcode, i8 value) {
        moduleweb_insn_list_byte(&mList, opcode, value);
        return *this;
    }

    InsnList& InsnList::shortInsn(Opcode opcode, i16 value) {
        moduleweb_insn_list_short(&mList, opcode, value);
        return *this;
    }

    InsnList& InsnList::intInsn(Opcode opcode, i32 value) {
        moduleweb_insn_list_int(&mList, opcode, value);
        return *this;
    }

    InsnList& InsnList::longInsn(Opcode opcode, i64 value) {
        moduleweb_insn_list_long(&mList, opcode, value);
        return *this;
    }

    Label* InsnList::createLabel(std::string_view name) {
        std::string temp(name);
        return createLabel(temp);
    }

    Label* InsnList::createLabel(std::string& name) {
        return moduleweb_insn_list_create_label(&mList, name.c_str());
    }

    InsnList& InsnList::addLabel(Label* label) {
        moduleweb_insn_list_add_label(&mList, label);
        return *this;
    }
}