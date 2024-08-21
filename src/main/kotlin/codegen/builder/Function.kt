package cum.jesus.jesusasm.codegen.builder

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.codegen.ModuleBytecodeBuffer
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.util.extensions.getModifierBits

class Function(private val output: ModuleBytecodeBuffer, private val section: Section) {
    val modifiers = mutableListOf<Modifier>()

    var entry: Long = 0

    /**
     * Index into the descriptor in the string table
     *
     * @see cum.jesus.jesusasm.codegen.builder.BytecodeBuilder.getString
     */
    var descriptor: UInt = 0u

    var localsCount: UShort = 0u
    var argumentCount: UShort = 0u

    fun emit() {
        output.write(modifiers.getModifierBits(), section)

        output.write(argumentCount, section)
        output.write(localsCount, section)

        output.write(descriptor, section)

        output.write(entry.toULong(), section);
    }
}