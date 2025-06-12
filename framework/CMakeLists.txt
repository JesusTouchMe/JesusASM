cmake_minimum_required(VERSION 3.26)

include(FetchContent)

FetchContent_Declare(
    JesusVM
    GIT_REPOSITORY https://github.com/JesusTouchMe/JesusVM.git
    GIT_TAG master
)

FetchContent_Declare(
        vlex
        GIT_REPOSITORY https://github.com/viper-org/vlex.git
        GIT_TAG master
)

FetchContent_MakeAvailable(JesusVM)
FetchContent_MakeAvailable(vlex)

set(SOURCES
    src/moduleweb-wrappers/OutStream.cpp
    src/moduleweb-wrappers/FieldBuilder.cpp
    src/moduleweb-wrappers/ClassBuilder.cpp
    src/moduleweb-wrappers/ModuleBuilder.cpp
    src/moduleweb-wrappers/ModuleInfo.cpp
    src/moduleweb-wrappers/FunctionBuilder.cpp
    src/tree/FieldNode.cpp
    src/tree/ClassNode.cpp
    src/tree/FunctionNode.cpp
    src/tree/ModuleNode.cpp
        src/tree/InsnList.cpp
        src/tree/instructions/InsnNode.cpp
        src/tree/instructions/CallInsnNode.cpp
        src/tree/instructions/IntInsnNode.cpp
        src/tree/instructions/LabelNode.cpp
        src/tree/instructions/JumpInsnNode.cpp
        src/tree/instructions/ClassInsnNode.cpp
        src/tree/instructions/FieldInsnNode.cpp
        src/tree/instructions/VarInsnNode.cpp
        src/type/Type.cpp
        src/parser/ExpressionParser.cpp
        src/parser/Parser.cpp
    src/tree/instructions/LdcInsnNode.cpp
        src/Attributes.cpp
    src/Opcodes.cpp
        src/moduleweb-wrappers/GlobalVarBuilder.cpp
        src/tree/GlobalVarNode.cpp
        src/tree/instructions/GlobalVarInsnNode.cpp
        src/moduleweb-wrappers/MethodBuilder.cpp
        src/tree/MethodNode.cpp
        src/tree/instructions/MethodInsnNode.cpp
    src/tree/instructions/IncInsnNode.cpp
)
set(HEADERS
    include/JesusASM/tree/ModuleNode.h
    include/JesusASM/Attribute.h
    include/JesusASM/moduleweb-wrappers/OutStream.h
    include/JesusASM/tree/ClassNode.h
    include/JesusASM/tree/FieldNode.h
    include/JesusASM/moduleweb-wrappers/FieldBuilder.h
    include/JesusASM/moduleweb-wrappers/ClassBuilder.h
    include/JesusASM/moduleweb-wrappers/ModuleBuilder.h
    include/JesusASM/moduleweb-wrappers/AttributeBuilder.h
    include/JesusASM/moduleweb-wrappers/ModuleInfo.h
    include/JesusASM/moduleweb-wrappers/FunctionBuilder.h
    include/JesusASM/Name.h
    include/JesusASM/tree/FunctionNode.h
    include/JesusASM/tree/InsnList.h
        include/JesusASM/tree/AbstractInsnNode.h
    include/JesusASM/Opcodes.h
        include/JesusASM/tree/instructions/InsnNode.h
        include/JesusASM/moduleweb-wrappers/InsnList.h
        src/moduleweb-wrappers/InsnList.cpp
        include/JesusASM/tree/instructions/CallInsnNode.h
        include/JesusASM/tree/instructions/IntInsnNode.h
        include/JesusASM/tree/instructions/LabelNode.h
        include/JesusASM/tree/instructions/JumpInsnNode.h
        include/JesusASM/tree/instructions/ClassInsnNode.h
        include/JesusASM/tree/instructions/FieldInsnNode.h
        include/JesusASM/tree/instructions/VarInsnNode.h
        include/JesusASM/parser/Parser.h
        include/JesusASM/parser/InstructionParser.h
        include/JesusASM/type/Type.h
        include/JesusASM/parser/ExpressionParser.h
        include/JesusASM/parser/TokenStream.h
    include/JesusASM/tree/instructions/LdcInsnNode.h
        include/JesusASM/Attributes.h
        include/JesusASM/moduleweb-wrappers/GlobalVarBuilder.h
        include/JesusASM/tree/GlobalVarNode.h
        include/JesusASM/tree/instructions/GlobalVarInsnNode.h
        include/JesusASM/moduleweb-wrappers/MethodBuilder.h
        include/JesusASM/tree/MethodNode.h
        include/JesusASM/tree/instructions/MethodInsnNode.h
        include/JesusASM/tree/instructions/IncInsnNode.h
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_library(jesusasm-framework ${SOURCES} ${HEADERS})
add_library(JesusASM::framework ALIAS jesusasm-framework)

vlex_generate(jesusasm-framework src/lexer/Lexer.vlex src/lexer include/JesusASM/lexer)

target_include_directories(jesusasm-framework
    PUBLIC
        include
)

if(WIN32)
    target_compile_definitions(jesusasm-framework PUBLIC PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(jesusasm-framework PUBLIC PLATFORM_MACOS)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(jesusasm-framework PUBLIC PLATFORM_LINUX)
endif()

target_compile_features(jesusasm-framework PUBLIC cxx_std_20)

add_dependencies(jesusasm-framework JesusVM::moduleweb)
target_link_libraries(jesusasm-framework PUBLIC JesusVM::moduleweb)
