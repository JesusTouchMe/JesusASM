package cum.jesus.jesusasm.type

class ClassType(val module: String, override val name: String) : Type {
    override val id: String = "T$module/$name;"

    override val primitiveId: UByte
        get() = throw RuntimeException("not primitive type")

    override fun equals(other: Any?): Boolean {
        return other is ClassType && other.id == id
    }
}