package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.environment.FunctionContext
import cum.jesus.jesusasm.type.FunctionType

class Function(val name: String, val type: FunctionType, val modifiers: Collection<Modifier>, val context: FunctionContext) : Value {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.function {
            modifiers.addAll(this@Function.modifiers)

            entry = builder.getPosition(Section.Bytecode);

            descriptor = builder.getString(name + type.id)

            localsCount = context.locals
            argumentCount = type.argumentTypes.size.toUShort()
        }

        builder.incFunctionCount()
    }
}