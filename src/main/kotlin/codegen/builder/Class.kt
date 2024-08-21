package cum.jesus.jesusasm.codegen.builder

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.codegen.ModuleBytecodeBuffer
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.util.extensions.getModifierBits

class Field(val descriptor: UInt, val name: UInt, val modifiers: List<Modifier>) {
    fun emit(output: ModuleBytecodeBuffer, section: Section) {
        output.write(descriptor, section)
        output.write(name, section)
        output.write(modifiers.getModifierBits(), section)
    }
}

class Method(val functionNameIndex: UInt) {
    fun emit(output: ModuleBytecodeBuffer, section: Section) {
        output.write(functionNameIndex, section)
    }
}

class Class(private val output: ModuleBytecodeBuffer, private val section: Section) {
    val modifiers = mutableListOf<Modifier>()

    var name: UInt = 0u
    var superClassModuleName: UInt = 0u
    var superClassName: UInt = 0u

    val fields = mutableListOf<Field>()
    val methods = mutableListOf<Method>()

    fun emit() {
        output.write(modifiers.getModifierBits(), section)

        output.write(name, section)
        output.write(superClassModuleName, section)
        output.write(superClassName, section)

        output.write(fields.size.toUShort(), section)
        output.write(methods.size.toUShort(), section)

        for (field in fields) {
            field.emit(output, section)
        }

        for (method in methods) {
            method.emit(output, section)
        }
    }
}