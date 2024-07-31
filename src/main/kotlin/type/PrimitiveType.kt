package cum.jesus.jesusasm.type

data class PrimitiveType(
    override val name: String,
    override val id: String,
    val sizeInBits: Int
) : Type