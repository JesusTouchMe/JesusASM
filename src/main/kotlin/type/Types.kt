package cum.jesus.jesusasm.type

private val namedTypes = mutableMapOf(
    "bool" to PrimitiveType("bool", "B", 0u, 1),
    "byte" to PrimitiveType("byte", "b", 1u, 8),
    "short" to PrimitiveType("short", "s", 2u,16),
    "int" to PrimitiveType("int", "i", 3u, 32),
    "long" to PrimitiveType("long", "l", 4u, 64),

    "void" to VoidType
)

private val types = mutableListOf<Type>()

fun isType(text: String): Boolean {
    return namedTypes.contains(text)
}

fun getType(name: String): Type? {
    return namedTypes[name]
}

fun getClassType(module: String, name: String): ClassType {
    for (type in types) {
        if (type is ClassType) {
            if (type.module == module && type.name == name) {
                return type
            }
        }
    }

    val type = ClassType(module, name)
    types.add(type)
    return type
}

fun getFunctionType(returnType: Type, argumentTypes: Array<Type>): FunctionType {
    for (type in types) {
        if (type is FunctionType) {
            if (type.returnType == returnType && type.argumentTypes.contentEquals(argumentTypes)) {
                return type
            }
        }
    }

    val type = FunctionType(returnType, argumentTypes.copyOf())
    types.add(type)
    return type
}

fun getFunctionType(returnType: Type, argumentTypes: Collection<Type>): FunctionType {
    return getFunctionType(returnType, argumentTypes.toTypedArray())
}