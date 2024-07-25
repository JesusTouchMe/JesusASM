package cum.jesus.jesusasm.util.extensions

fun Char.isHexDigit(): Boolean {
    return this in "1234567890abcdefABCDEF"
}

fun Char.isOctDigit(): Boolean {
    return this in '0'..'7'
}

fun Char.isBinDigit(): Boolean {
    return this == '0' || this == '1'
}