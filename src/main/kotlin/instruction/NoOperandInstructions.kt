/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import java.io.PrintStream

open class NoOperandInstruction(val opcode: Opcode, val name: String) : Instruction {
    override fun print(stream: PrintStream): Boolean {
        stream.print(name)
        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = this@NoOperandInstruction.opcode
        }
    }
}

class NopInstruction : NoOperandInstruction(NOP, "nop")
class PopInstruction : NoOperandInstruction(POP, "pop")
class DupInstruction : NoOperandInstruction(DUP, "dup")

class ALoadInstruction : NoOperandInstruction(ALOAD, "aload")
class AStoreInstruction : NoOperandInstruction(ASTORE, "astore")
class ALoadObjInstruction : NoOperandInstruction(ALOADOBJ, "aloadobj")
class AStoreObjInstruction : NoOperandInstruction(ASTOREOBJ, "astoreobj")

class AddInstruction : NoOperandInstruction(ADD, "add")
class SubInstruction : NoOperandInstruction(SUB, "sub")
class MulInstruction : NoOperandInstruction(MUL, "mul")
class DivInstruction : NoOperandInstruction(DIV, "div")
class AndInstruction : NoOperandInstruction(AND, "and")
class OrInstruction : NoOperandInstruction(OR, "or")
class XorInstruction : NoOperandInstruction(XOR, "xor")

class IncInstruction : NoOperandInstruction(INC, "inc")
class DecInstruction : NoOperandInstruction(DEC, "dec")
class NotInstruction : NoOperandInstruction(NOT, "not")
class NegInstruction : NoOperandInstruction(NEG, "neg")

class CmpInstruction : NoOperandInstruction(CMP, "cmp")

class RetInstruction : NoOperandInstruction(RET, "ret")

class Ldi0Instruction : NoOperandInstruction(LDI_0, "ldi_0")

class DebugInstruction : NoOperandInstruction(DEBUG, "debug") {
    init {
        println("WARNING: Use of the 'debug' instruction may potentially cause the VM to crash if it's not run in debug mode")
    }
}

class HltInstruction : NoOperandInstruction(HLT, "hlt")