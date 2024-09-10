package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize
import java.io.PrintStream

class LdcInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("ldc ${size.name} $index")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = LDC
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