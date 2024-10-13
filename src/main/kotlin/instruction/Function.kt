package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.environment.FunctionContext
import cum.jesus.jesusasm.type.FunctionType
import java.io.PrintStream

class Function(val name: String, val type: FunctionType, val modifiers: Collection<Modifier>, val context: FunctionContext) : Value {
    override fun print(stream: PrintStream): Boolean {
        stream.print("\nfunction ${modifiers.joinToString(" ") { it.name.lowercase() }} ${type.returnType.name} $name")
        stream.print(type.argumentTypes.joinToString(prefix = "(", postfix = ")") { it.name })
        stream.print(":")

        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.function {
            modifiers.addAll(this@Function.modifiers)

            entry = builder.getPosition("code");

            descriptor = builder.getString(name + type.id)

            localsCount = context.localCount
            argumentCount = type.argumentTypes.size.toUShort()
        }

        builder.incFunctionCount()
    }
}