package cum.jesus.jesusasm.type

data class PrimitiveType(
    override val name: String,
    override val id: String,
    override val primitiveId: UByte,
    val sizeInBits: Int
) : Type