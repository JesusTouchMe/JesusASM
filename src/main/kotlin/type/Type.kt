package cum.jesus.jesusasm.type

sealed interface Type {
    val name: String
    val id: String

    override operator fun equals(other: Any?): Boolean
}