package cum.jesus.jesusasm.codegen.builder

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.codegen.ModuleBytecodeBuffer
import cum.jesus.jesusasm.codegen.Section

class Function(private val output: ModuleBytecodeBuffer, private val section: Section) {
    val modifiers = mutableListOf<Modifier>()

    /**
     * Index into the descriptor in the string table
     *
     * @see cum.jesus.jesusasm.codegen.builder.BytecodeBuilder.getString
     */
    var descriptor: UInt = 0u

    fun emit() {
        output.write(69.toUByte(), section) // some magic number so it knows the difference between a function declaration and padding

        val bits = getModifierBits()
        output.write(bits, section)

        output.write(descriptor, section)
    }

    private fun getModifierBits(): UShort {
        var bits: UShort = 0u

        for (modifier in modifiers) {
            bits = bits or modifier.bitmask
        }

        return bits
    }
}