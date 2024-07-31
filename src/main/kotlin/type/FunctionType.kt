package cum.jesus.jesusasm.type

data class FunctionType(val returnType: Type, val argumentTypes: Array<Type>) : Type {
    override val name: String
    override val id: String

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
}