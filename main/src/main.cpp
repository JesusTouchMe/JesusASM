// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/ModuleNode.h"

#include "JesusASM/tree/instructions/CallInsnNode.h"
#include "JesusASM/tree/instructions/ClassInsnNode.h"
#include "JesusASM/tree/instructions/FieldInsnNode.h"
#include "JesusASM/tree/instructions/InsnNode.h"
#include "JesusASM/tree/instructions/IntInsnNode.h"
#include "JesusASM/tree/instructions/JumpInsnNode.h"
#include "JesusASM/tree/instructions/LabelNode.h"
#include "JesusASM/tree/instructions/VarInsnNode.h"

#include <iostream>

void GenerateMain() {
    JesusASM::tree::ModuleNode module(1, std::string_view("Main"));

    auto vec2 = std::make_unique<JesusASM::tree::ClassNode>(MODULEWEB_CLASS_MODIFIER_PUBLIC,
                                                            std::string_view("Vec2"), nullptr);

    vec2->fields.push_back(std::make_unique<JesusASM::tree::FieldNode>(MODULEWEB_FIELD_MODIFIER_PUBLIC,
                                                                       std::string_view("x"), "I"));

    vec2->fields.push_back(std::make_unique<JesusASM::tree::FieldNode>(MODULEWEB_FIELD_MODIFIER_PUBLIC,
                                                                       std::string_view("y"), "I"));

    module.classes.push_back(std::move(vec2));

    module.functions.push_back(std::make_unique<JesusASM::tree::FunctionNode>(
            MODULEWEB_FUNCTION_MODIFIER_PUBLIC | MODULEWEB_FUNCTION_MODIFIER_NATIVE,
            std::string_view("print"), "(I)V"));

    auto mainFunc = std::make_unique<JesusASM::tree::FunctionNode>(MODULEWEB_FUNCTION_MODIFIER_PUBLIC,
                                                                   std::string_view("main"), "()V");

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::ClassInsnNode>(JesusASM::Opcodes::NEW, "Main:Vec2"));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::InsnNode>(JesusASM::Opcodes::DUP2));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::IntInsnNode>(JesusASM::Opcodes::IPUSH, JesusASM::tree::OperandSize::INT, 34i64));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::FieldInsnNode>(JesusASM::Opcodes::SETFIELD, "Main:Vec2", "x", "I"));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::InsnNode>(JesusASM::Opcodes::DUP2));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::IntInsnNode>(JesusASM::Opcodes::IPUSH, JesusASM::tree::OperandSize::INT, 35i64));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::FieldInsnNode>(JesusASM::Opcodes::SETFIELD, "Main:Vec2", "y", "I"));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::VarInsnNode>(JesusASM::Opcodes::RSTORE, 0));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::InsnNode>(JesusASM::Opcodes::RLOAD_0));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::FieldInsnNode>(JesusASM::Opcodes::GETFIELD, "Main:Vec2", "x", "I"));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::InsnNode>(JesusASM::Opcodes::RLOAD_0));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::FieldInsnNode>(JesusASM::Opcodes::GETFIELD, "Main:Vec2", "y", "I"));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::InsnNode>(JesusASM::Opcodes::ADD));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::CallInsnNode>(JesusASM::Opcodes::CALL, std::string_view("Main"), "print", "(I)V"));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::InsnNode>(JesusASM::Opcodes::RETURN));

    module.functions.push_back(std::move(mainFunc));

    moduleweb::ModuleBuilder builder;
    moduleweb::ModuleInfo info;

    module.emit(builder, info);

    info.print();

    moduleweb::FileOutStream out("Main.jmod");
    info.emit(out);

    out.flush();
}

void GenerateVMSystem() {
    JesusASM::tree::ModuleNode module(1, std::string_view("vm/System"));

    module.functions.push_back(std::make_unique<JesusASM::tree::FunctionNode>(
            MODULEWEB_FUNCTION_MODIFIER_PUBLIC | MODULEWEB_FUNCTION_MODIFIER_NATIVE,
            std::string_view("exit"), "(I)V"));

    moduleweb::ModuleBuilder builder;
    moduleweb::ModuleInfo info;

    module.emit(builder, info);

    info.print();

    moduleweb::FileOutStream out("vm/System.jmod");
    info.emit(out);

    out.flush();
}

int main(int argc, char** argv) {
    GenerateVMSystem();
    GenerateMain();

    return 0;
}