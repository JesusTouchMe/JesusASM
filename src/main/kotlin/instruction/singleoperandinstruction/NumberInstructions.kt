package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import java.io.PrintStream

class ByteInstruction(val value: UByte) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("byte $value")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.output.write(value, builder.section)
    }
}

class ShortInstruction(val value: UShort) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("short $value")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.output.write(value, builder.section)
    }
}

class IntInstruction(val value: UInt) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("int $value")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.output.write(value, builder.section)
    }
}

class LongInstruction(val value: ULong) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print("long $value")
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.output.write(value, builder.section)
    }
}
