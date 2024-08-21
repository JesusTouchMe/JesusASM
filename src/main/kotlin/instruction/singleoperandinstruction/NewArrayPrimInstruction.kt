package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.OperandSize
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize

class NewArrayPrimInstruction(val primTypeId: UByte) : Instruction {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction {
            opcode = NEWARRAYPRIM
            immediate = primTypeId.toULong()
            immediateSize = OperandSize.Byte
        }
    }
}