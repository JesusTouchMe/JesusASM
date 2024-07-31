package cum.jesus.jesusasm.type

interface Type {
    val name: String
    val id: String

    override operator fun equals(other: Any?): Boolean
}