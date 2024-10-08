/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import java.io.PrintStream

class Label(val name: String) : Value {
    override fun print(stream: PrintStream): Boolean {
        stream.print("$name:")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.addLabel(name, section)
    }
}