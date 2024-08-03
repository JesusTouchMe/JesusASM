package cum.jesus.jesusasm.util

import cum.jesus.jesusasm.codegen.OperandSize

fun getImmediateSize(immediate: ULong): OperandSize {
    return when {
        immediate <= UByte.MAX_VALUE.toULong() -> OperandSize.Byte
        immediate <= UShort.MAX_VALUE.toULong() -> OperandSize.Short
        immediate <= UInt.MAX_VALUE.toULong() -> OperandSize.Int
        immediate <= ULong.MAX_VALUE -> OperandSize.Long

        else -> OperandSize.None
    }
}

fun getImmediateSize(immediate: Long): OperandSize {
    return when (immediate) {
        in Byte.MIN_VALUE..Byte.MAX_VALUE -> OperandSize.Byte
        in Short.MIN_VALUE..Short.MAX_VALUE -> OperandSize.Short
        in Int.MIN_VALUE..Int.MAX_VALUE -> OperandSize.Int
        else -> OperandSize.Long
    }
}