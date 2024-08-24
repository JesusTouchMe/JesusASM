package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.util.getImmediateSize
import java.io.PrintStream

class LoadInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("load ${size.name} $index")
        return true
    }

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

class LoadObjInstruction(val index: ULong, val size: OperandSize = getImmediateSize(index)) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("loadobj ${size.name} $index")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = LOADOBJ
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