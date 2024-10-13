package cum.jesus.jesusasm.environment

import cum.jesus.jesusasm.instruction.Field
import cum.jesus.jesusasm.instruction.Method
import cum.jesus.jesusasm.util.WriteOnceProperty

class GlobalContext {
    val defines = mutableMapOf<String, ULong>()

    val constants = mutableMapOf<String, UInt>()
    private var constantIndex = 0u

    fun addConstant(name: String) {
        if (constants.contains(name)) {
            throw RuntimeException("constant $name already exists")
        }

        constants[name] = constantIndex++
    }

    fun defineConstant(name: String, value: ULong) {
        if (defines.contains(name)) {
            throw RuntimeException("$name is already defined as ${defines[name]}")
        }

        defines[name] = value
    }
}

class FunctionContext {
    val locals = mutableMapOf<String, UShort>()
    var localCount by WriteOnceProperty<UShort>(0u)
}

class ClassContext(val name: String) {
    val fields = mutableListOf<Field>()
    val methods = mutableListOf<Method>()
}