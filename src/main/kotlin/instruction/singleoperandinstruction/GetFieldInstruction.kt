package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize
import java.io.PrintStream

class GetFieldInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("getfield ${size.name} $index")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction {
            opcode = GETFIELD
            immediate = index
            immediateSize = size

            when (size) {
                OperandSize.Byte, OperandSize.Short -> immediateSize = OperandSize.Int
                OperandSize.Int -> {}
                OperandSize.Long -> prefix = WIDE

                OperandSize.None -> {
                    throw RuntimeException("no size given to getfield")
                }
            }
        }
    }
}