/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.codegen.builder

import cum.jesus.jesusasm.codegen.*

class Instruction(private val output: ModuleBytecodeBuffer, private val section: Section) {
    var prefix: Prefix? = null
    var opcode: Opcode? = null

    var immediate: ULong? = null
    var immediateSize: OperandSize = OperandSize.None

    var string: String? = null

    fun emit() {
        if (prefix != null) output.write(prefix!!, section)
        if (opcode != null) output.write(opcode!!, section)

        if (immediate != null && immediateSize != OperandSize.None) {
            when (immediateSize) {
                OperandSize.Byte -> {
                    output.write(immediate!!.toUByte(), section)
                }

                OperandSize.Short -> {
                    output.write(immediate!!.toUShort(), section)
                }

                OperandSize.Int -> {
                    output.write(immediate!!.toUInt(), section)
                }

                OperandSize.Long -> {
                    output.write(immediate!!, section)
                }

                else -> {
                    throw RuntimeException("unreachable")
                }
            }
        }

        if (string != null) output.write(string!!, section)
    }
}