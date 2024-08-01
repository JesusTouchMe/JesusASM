package cum.jesus.jesusasm.codegen.builder

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.codegen.ModuleBytecodeBuffer
import cum.jesus.jesusasm.codegen.Section

class Function(private val output: ModuleBytecodeBuffer, private val section: Section) {
    val modifiers = mutableListOf<Modifier>()

    var name: String? = null
    var descriptor: String? = null

    fun emit() {

    }

    private fun getModifierBits(): UShort {
        var bits: UShort = 0u

        for (modifier in modifiers) {
            bits = bits or modifier.bitmask
        }

        return bits
    }
}