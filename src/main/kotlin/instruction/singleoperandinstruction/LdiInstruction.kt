package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.LDI
import cum.jesus.jesusasm.codegen.OperandSize
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.WIDE
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize

class LdiInstruction(val value: ULong, val size: OperandSize = getImmediateSize(value)) : Instruction {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = LDI
            immediate = value
            immediateSize = size

            when (size) {
                OperandSize.Byte, OperandSize.Short -> immediateSize = OperandSize.Int
                OperandSize.Int -> {}
                OperandSize.Long -> prefix = WIDE

                OperandSize.None -> {
                    throw RuntimeException("no size given to ldi")
                }
            }
        }
    }
}