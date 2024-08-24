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
        builder.section = getSection()
    }

    private fun getSection(): Section {
        return when (name) {
            "functions" -> Section.Functions
            "classes" -> Section.Classes
            "constpool" -> Section.ConstPool
            "code" -> Section.Bytecode

            else -> throw RuntimeException("bad section name $name")
        }
    }
}

class SectionDirective2(val section: Section) : Directive {
    override fun print(stream: PrintStream): Boolean {
        stream.print("\nsection ${section.name.lowercase()}")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.section = this.section
    }
}