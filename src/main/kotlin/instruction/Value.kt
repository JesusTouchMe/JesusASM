/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import java.io.PrintStream

interface Value {
    fun print(stream: PrintStream): Boolean // true if something was printed

    fun emit(builder: BytecodeBuilder, section: Section)
}