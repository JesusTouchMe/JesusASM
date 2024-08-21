package cum.jesus.jesusasm.codegen.builder

import cum.jesus.jesusasm.codegen.ConstantKind
import cum.jesus.jesusasm.codegen.ModuleBytecodeBuffer
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.constants.ClassSymbol
import cum.jesus.jesusasm.codegen.builder.constants.FieldSymbol
import cum.jesus.jesusasm.codegen.builder.constants.FunctionSymbol
import cum.jesus.jesusasm.codegen.builder.constants.MethodSymbol

class Constant(private val output: ModuleBytecodeBuffer, private val section: Section) {
    var kind: ConstantKind? = null

    private var value: Any? = null

    var function: FunctionSymbol
        get() = throw UnsupportedOperationException()
        set(value) { this.value = value }

    var clas: ClassSymbol
        get() = throw UnsupportedOperationException()
        set(value) { this.value = value }

    var field: FieldSymbol
        get() = throw UnsupportedOperationException()
        set(value) { this.value = value }

    var method: MethodSymbol
        get() = throw UnsupportedOperationException()
        set(value) { this.value = value }

    fun emit() {
        if (kind != null) output.write(kind!!.byte, section)

        if (value != null) {
            when (val value = value!!) {
                is FunctionSymbol -> {
                    require(kind == ConstantKind.Function)

                    output.write(value.module, section)
                    output.write(value.descriptor, section)
                }

                is ClassSymbol -> {
                    require(kind == ConstantKind.Class)

                    output.write(value.module, section)
                    output.write(value.name, section)
                }

                is FieldSymbol -> {
                    require(kind == ConstantKind.Field)

                    output.write(value.module, section)
                    output.write(value.clas, section)
                    output.write(value.name, section)
                }

                is MethodSymbol -> {
                    require(kind == ConstantKind.Method)

                    output.write(value.module, section)
                    output.write(value.clas, section)
                    output.write(value.descriptor, section)
                }
            }
        }
    }
}