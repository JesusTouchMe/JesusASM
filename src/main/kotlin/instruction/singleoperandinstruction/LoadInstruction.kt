package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.LOAD
import cum.jesus.jesusasm.codegen.OperandSize
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.WIDE
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize

class LoadInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = LOAD
            immediate = index
            immediateSize = size

            when (size) {
                OperandSize.Byte -> {}
                OperandSize.Short -> {
                    prefix = WIDE
                }

                else -> {
                    throw RuntimeException("too large operand for load instruction")
                }
            }
        }
    }
}