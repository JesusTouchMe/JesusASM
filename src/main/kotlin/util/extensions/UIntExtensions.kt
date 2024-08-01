package cum.jesus.jesusasm.util.extensions

fun UInt.align16(): UInt {
    return (this + 15u) and 15u.inv()
}