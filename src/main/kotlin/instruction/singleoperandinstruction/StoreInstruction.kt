package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize
import java.io.PrintStream

class StoreInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("store ${size.name} $index")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = STORE
            immediate = index
            immediateSize = size

            when (size) {
                OperandSize.Byte -> {}
                OperandSize.Short -> {
                    prefix = WIDE
                }

                else -> {
                    throw RuntimeException("too large operand for store instruction")
                }
            }
        }
    }
}

class StoreObjInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("storeobj ${size.name} $index")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = STOREOBJ
            immediate = index
            immediateSize = size

            when (size) {
                OperandSize.Byte -> {}
                OperandSize.Short -> {
                    prefix = WIDE
                }

                else -> {
                    throw RuntimeException("too large operand for store instruction")
                }
            }
        }
    }
}