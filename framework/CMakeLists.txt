cmake_minimum_required(VERSION 3.26)

include(FetchContent)

FetchContent_Declare(
    moduleweb
    GIT_REPOSITORY https://github.com/JesusTouchMe/JesusVM.git
    GIT_TAG master
    SOURCE_SUBDIR moduleweb
)

FetchContent_MakeAvailable(moduleweb)

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
    src/Attribute.cpp
    src/tree/InsnList.cpp
        src/tree/instructions/InsnNode.cpp
        src/tree/instructions/CallInsnNode.cpp
        src/tree/instructions/IntInsnNode.cpp
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
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_library(jesusasm-framework-jesusasm-framework ${SOURCES} ${HEADERS})
add_library(JesusASM::framework ALIAS jesusasm-framework-jesusasm-framework)

target_include_directories(jesusasm-framework-jesusasm-framework
    PUBLIC
        include
)

if(WIN32)
    target_compile_definitions(jesusasm-framework-jesusasm-framework PUBLIC PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(jesusasm-framework-jesusasm-framework PUBLIC PLATFORM_MACOS)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(jesusasm-framework-jesusasm-framework PUBLIC PLATFORM_LINUX)
endif()

target_compile_features(jesusasm-framework-jesusasm-framework PUBLIC cxx_std_20)

add_dependencies(jesusasm-framework-jesusasm-framework JesusVM::moduleweb)
target_link_libraries(jesusasm-framework-jesusasm-framework PUBLIC JesusVM::moduleweb)
