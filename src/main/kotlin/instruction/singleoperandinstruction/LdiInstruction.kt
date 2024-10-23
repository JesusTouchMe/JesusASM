package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize
import java.io.PrintStream

class LdiInstruction(val value: ULong, val size: OperandSize = getImmediateSize(value)) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("ldi ${size.name} $value")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        if (value == 0uL) {
            builder.instruction(section) {
                opcode = LDI_0
            }

            return
        }

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