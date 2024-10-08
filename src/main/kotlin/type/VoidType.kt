package cum.jesus.jesusasm.type

object VoidType : Type {
    override val name = "void"
    override val id = "V"

    override val primitiveId: UByte
        get() = throw RuntimeException("not primitive type")

    override fun equals(other: Any?): Boolean {
        return other is VoidType
    }
}