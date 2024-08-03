package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize

class ConstLoadInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = CONSTLOAD
            immediate = index
            immediateSize = size

            when (size) {
                OperandSize.Byte -> immediateSize = OperandSize.Short
                OperandSize.Short -> {}
                OperandSize.Int -> prefix = WIDE

                else -> {
                    throw RuntimeException("too large operand for constload instruction")
                }
            }
        }
    }
}