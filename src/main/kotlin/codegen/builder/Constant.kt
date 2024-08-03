package cum.jesus.jesusasm.codegen.builder

import cum.jesus.jesusasm.codegen.ConstantKind
import cum.jesus.jesusasm.codegen.ModuleBytecodeBuffer
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.constants.FunctionSymbol

class Constant(private val output: ModuleBytecodeBuffer, private val section: Section) {
    var kind: ConstantKind? = null

    private var value: Any? = null

    var function: FunctionSymbol
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
            }
        }
    }
}