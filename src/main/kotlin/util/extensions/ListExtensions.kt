package cum.jesus.jesusasm.util.extensions

import cum.jesus.jesusasm.codegen.Modifier

fun List<Modifier>.getModifierBits(): UShort {
    var bits: UShort = 0u

    for (modifier in this) {
        bits = bits or modifier.bitmask
    }

    return bits
}