package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.type.FunctionType

class Function(val name: String, val type: FunctionType, val modifiers: Collection<Modifier>) : Value {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.function {
            modifiers.addAll(this@Function.modifiers)
            descriptor = builder.getString(name + type.id)
        }
    }
}