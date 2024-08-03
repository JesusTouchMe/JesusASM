package cum.jesus.jesusasm.environment

import cum.jesus.jesusasm.util.WriteOnceProperty

class GlobalContext {
    val constants = mutableMapOf<String, UInt>()
    private var constantIndex = 0u

    fun addConstant(name: String) {
        if (constants.contains(name)) {
            throw RuntimeException("constant $name already exists")
        }

        constants[name] = constantIndex++
    }
}

class FunctionContext {
    var locals by WriteOnceProperty<UShort>(0u)
}