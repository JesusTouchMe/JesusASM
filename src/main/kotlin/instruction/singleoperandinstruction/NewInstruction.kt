package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.NEW
import cum.jesus.jesusasm.codegen.OperandSize
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.WIDE
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize

class NewInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction {
            opcode = NEW
            immediate = index
            immediateSize = size

            when (size) {
                OperandSize.Byte, OperandSize.Short -> immediateSize = OperandSize.Int
                OperandSize.Int -> {}
                OperandSize.Long -> prefix = WIDE

                OperandSize.None -> {
                    throw RuntimeException("no size given to new")
                }
            }
        }
    }
}