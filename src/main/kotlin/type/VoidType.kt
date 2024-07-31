package cum.jesus.jesusasm.type

object VoidType : Type {
    override val name = "void"
    override val id = "V"

    override fun equals(other: Any?): Boolean {
        return other != null && other is VoidType
    }
}