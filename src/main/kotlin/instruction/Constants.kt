package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.ConstantKind
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.codegen.builder.constants.ClassSymbol
import cum.jesus.jesusasm.codegen.builder.constants.FieldSymbol
import cum.jesus.jesusasm.codegen.builder.constants.FunctionSymbol
import cum.jesus.jesusasm.codegen.builder.constants.MethodSymbol
import cum.jesus.jesusasm.type.FunctionType
import java.io.PrintStream

interface Constant : Value

class ConstantFunction(val module: String, val name: String, val functionType: FunctionType) : Constant {
    override fun print(stream: PrintStream): Boolean {
        if (module.isEmpty()) {
            stream.print(".function ${functionType.returnType.name} $name")
        } else {
            stream.print(".function ${functionType.returnType.name} $module/$name")
        }
        stream.print(functionType.argumentTypes.joinToString(prefix = "(", postfix = ")") { it.name })

        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.constant(section) {
            kind = ConstantKind.Function

            function = if (module.isEmpty()) {
                FunctionSymbol(0u, builder.getString(name + functionType.id))
            } else {
                FunctionSymbol(builder.getString(module), builder.getString(name + functionType.id))
            }
        }

        builder.incConstPoolElementCount()
    }
}

class ConstantClass(val module: String, val name: String) : Constant {
    override fun print(stream: PrintStream): Boolean {
        if (module.isEmpty()) {
            stream.print(".class $name")
        } else {
            stream.print(".class $module/$name")
        }

        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.constant(section) {
            kind = ConstantKind.Class

            clas = if (module.isEmpty()) {
                ClassSymbol(0u, builder.getString(name))
            } else {
                ClassSymbol(builder.getString(module), builder.getString(name))
            }
        }

        builder.incConstPoolElementCount()
    }
}

class ConstantField(val module: String, val clas: String, val name: String) : Constant {
    override fun print(stream: PrintStream): Boolean {
        if (module.isEmpty()) {
            stream.print(".field $clas::$name")
        } else {
            stream.print(".field $module/$clas::$name")
        }

        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.constant(section) {
            kind = ConstantKind.Field

            field = if (module.isEmpty()) {
                FieldSymbol(0u, builder.getString(this@ConstantField.clas), builder.getString(name))
            } else {
                FieldSymbol(builder.getString(module), builder.getString(this@ConstantField.clas), builder.getString(name))
            }
        }

        builder.incConstPoolElementCount()
    }
}

class ConstantMethod(val module: String, val clas: String, val name: String, val functionType: FunctionType) : Constant {
    override fun print(stream: PrintStream): Boolean {
        if (module.isEmpty()) {
            stream.print(".method ${functionType.returnType.name} $clas::$name")
        } else {
            stream.print(".method ${functionType.returnType.name} $module/$clas::$name")
        }

        stream.print(functionType.argumentTypes.joinToString(prefix = "(", postfix = ")") { it.name })

        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.constant(section) {
            kind = ConstantKind.Method

            method = if (module.isEmpty()) {
                MethodSymbol(0u, builder.getString(this@ConstantMethod.clas), builder.getString(name + functionType.id))
            } else {
                MethodSymbol(builder.getString(module), builder.getString(this@ConstantMethod.clas), builder.getString(name + functionType.id))
            }
        }

        builder.incConstPoolElementCount()
    }
}
