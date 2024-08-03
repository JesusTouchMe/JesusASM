package cum.jesus.jesusasm.instruction.operand

import cum.jesus.jesusasm.codegen.OperandSize
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder

class LabelOperand(val name: String) {
    fun getValue(builder: BytecodeBuilder, section: Section): Long {
        if (name == "$") {
            return builder.getPosition(section)
        }

        return builder.getLabel(name)
    }

    fun forward(builder: BytecodeBuilder, section: Section, size: OperandSize, offset: Int = 0) {
        if (name != "$") {
            if (builder.getLabel(name).toInt() == -1) {
                builder.forwardLabel(name, section, size, offset)
            }
        }
    }
}