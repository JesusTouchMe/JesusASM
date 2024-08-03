package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.CALL
import cum.jesus.jesusasm.codegen.OperandSize
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.WIDE
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize

class CallInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = CALL
            immediate = index
            immediateSize = size

            when (size) {
                OperandSize.Byte -> immediateSize = OperandSize.Short
                OperandSize.Short -> {}
                OperandSize.Int -> prefix = WIDE

                else -> {
                    throw RuntimeException("too large operand for call instruction")
                }
            }
        }
    }
}