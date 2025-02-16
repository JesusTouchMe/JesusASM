cmake_minimum_required(VERSION 3.26)

set(SOURCES "src/main.cpp")

set(HEADERS)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_executable(JesusASM ${SOURCES} ${HEADERS})
add_executable(JesusASM::main ALIAS JesusASM)

target_include_directories(JesusASM
    PUBLIC
        include
)

target_compile_features(JesusASM PUBLIC cxx_std_20)
target_link_libraries(JesusASM JesusASM::framework)