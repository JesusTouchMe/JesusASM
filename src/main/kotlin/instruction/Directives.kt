package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import java.io.PrintStream

interface Directive : Value

class SectionDirective(val name: String) : Directive {
    override fun print(stream: PrintStream): Boolean {
        stream.print("\nsection $name")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.section = builder.getSection(name)
    }
}