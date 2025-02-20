// Copyright 2025 JesusTouchMe

#include "JesusASM/tree/ModuleNode.h"

#include "JesusASM/tree/instructions/CallInsnNode.h"
#include "JesusASM/tree/instructions/InsnNode.h"
#include "JesusASM/tree/instructions/IntInsnNode.h"
#include "JesusASM/tree/instructions/JumpInsnNode.h"
#include "JesusASM/tree/instructions/LabelNode.h"

#include <iostream>

int main(int argc, char** argv) {
    JesusASM::tree::ModuleNode module(1, std::string_view("Main"));

    module.functions.push_back(std::make_unique<JesusASM::tree::FunctionNode>(
            MODULEWEB_FUNCTION_MODIFIER_PUBLIC | MODULEWEB_FUNCTION_MODIFIER_NATIVE,
            std::string_view("print"), "(I)V"));

    auto mainFunc = std::make_unique<JesusASM::tree::FunctionNode>(MODULEWEB_FUNCTION_MODIFIER_PUBLIC, std::string_view("main"), "()V");

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::IntInsnNode>(JesusASM::Opcodes::IPUSH, JesusASM::tree::OperandSize::INT, 2i64));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::IntInsnNode>(JesusASM::Opcodes::IPUSH, JesusASM::tree::OperandSize::INT, 2i64));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::InsnNode>(JesusASM::Opcodes::ADD));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::IntInsnNode>(JesusASM::Opcodes::IPUSH, JesusASM::tree::OperandSize::INT, 4i64));

    auto equal = std::make_unique<JesusASM::tree::LabelNode>(std::string_view("equal"));
    auto end = std::make_unique<JesusASM::tree::LabelNode>(std::string_view("end"));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::JumpInsnNode>(JesusASM::Opcodes::JMP_ICMPEQ, equal.get()));

    mainFunc->instructions.add(std::make_unique<JesusASM::tree::InsnNode>(JesusASM::Opcodes::CONST_0));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::JumpInsnNode>(JesusASM::Opcodes::JMP, end.get()));

    mainFunc->instructions.add(std::move(equal));
    mainFunc->instructions.add(std::make_unique<JesusASM::tree::InsnNode>(JesusASM::Opcodes::CONST_1));

    mainFunc->instructions.add(std::move(end));

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

    return 0;
}