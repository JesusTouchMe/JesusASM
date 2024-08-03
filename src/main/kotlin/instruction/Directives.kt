package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder

class SectionDirective(val name: String) : Value {
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