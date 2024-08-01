package cum.jesus.jesusasm.codegen.builder

import cum.jesus.jesusasm.codegen.*

class Instruction(private val output: ModuleBytecodeBuffer, private val section: Section) {
    var prefix: Prefix? = null
    var opcode: Opcode? = null

    var immediate: Any? = null
        set(value)  {
            when (value) {
                is Byte, is Short, is Int, is Long,
                is UByte, is UShort, is UInt, is ULong, null -> field = value

                else -> throw IllegalArgumentException("Immediate can only be a valid immediate type")
            }
        }

    var string: String? = null

    fun emit() {
        if (prefix != null) output.write(prefix!!, section)
        if (opcode != null) output.write(opcode!!, section)

        if (immediate != null) {
            when (val immediate = immediate!!) {
                is Byte -> output.write(immediate.toUByte(), section)
                is UByte -> output.write(immediate, section)

                is Short -> output.write(immediate.toUShort(), section)
                is UShort -> output.write(immediate, section)

                is Int -> output.write(immediate.toUInt(), section)
                is UInt -> output.write(immediate, section)

                is Long -> output.write(immediate.toULong(), section)
                is ULong -> output.write(immediate, section)
            }
        }

        if (string != null) output.write(string!!, section)
    }
}