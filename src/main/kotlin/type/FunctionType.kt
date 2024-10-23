package cum.jesus.jesusasm.type

data class FunctionType(val returnType: Type, val argumentTypes: Array<Type>) : Type {
    override val name: String
    override val id: String

    override val primitiveId: UByte
        get() = throw RuntimeException("not primitive type")

    init {
        val sb = StringBuilder()

        sb.append(returnType.name).append('(')
        argumentTypes.joinTo(sb, ", ", transform = { it.name })
        sb.append(')')

        name = sb.toString()
        sb.clear()

        sb.append('(')
        argumentTypes.joinTo(sb, "", transform = { it.id })
        sb.append(')')
        sb.append(returnType.id)

        id = sb.toString()
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as FunctionType

        if (returnType != other.returnType) return false
        if (!argumentTypes.contentEquals(other.argumentTypes)) return false
        if (name != other.name) return false
        if (id != other.id) return false

        return true
    }

    override fun hashCode(): Int {
        var result = returnType.hashCode()
        result = 31 * result + argumentTypes.contentHashCode()
        result = 31 * result + name.hashCode()
        result = 31 * result + id.hashCode()
        return result
    }
}