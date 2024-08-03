package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.ConstantKind
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.codegen.builder.constants.FunctionSymbol
import cum.jesus.jesusasm.type.FunctionType

class ConstantFunction(val module: String, val name: String, val functionType: FunctionType) : Value {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.constant(section) {
            kind = ConstantKind.Function

            function = if (module.isEmpty()) {
                FunctionSymbol(0u, builder.getString(name + functionType.id))
            } else {
                FunctionSymbol(builder.getString(module), builder.getString(name + functionType.id))
            }
        }
    }
}