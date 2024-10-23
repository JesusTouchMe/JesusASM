/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import java.io.PrintStream

sealed class NoOperandInstruction(val opcode: Opcode, val name: String) : Instruction {
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
class ShrInstruction : NoOperandInstruction(SHR, "shr")
class ShlInstruction : NoOperandInstruction(SHL, "shl")

class IncInstruction : NoOperandInstruction(INC, "inc")
class DecInstruction : NoOperandInstruction(DEC, "dec")
class NotInstruction : NoOperandInstruction(NOT, "not")
class NegInstruction : NoOperandInstruction(NEG, "neg")

class CmpInstruction : NoOperandInstruction(CMP, "cmp")
class CmpTrueInstruction : NoOperandInstruction(CMP_TRUE, "cmp_true")
class CmpFalseInstruction : NoOperandInstruction(CMP_FALSE, "cmp_false")

class PushEqInstruction : NoOperandInstruction(PUSHEQ, "pusheq")
class PushNeInstruction : NoOperandInstruction(PUSHNE, "pushne")
class PushLtInstruction : NoOperandInstruction(PUSHLT, "pushlt")
class PushGtInstruction : NoOperandInstruction(PUSHGT, "pushgt")
class PushLeInstruction : NoOperandInstruction(PUSHLE, "pushle")
class PushGeInstruction : NoOperandInstruction(PUSHGE, "pushge")

class RetInstruction : NoOperandInstruction(RET, "ret")

class DebugInstruction : NoOperandInstruction(DEBUG, "debug") {
    init {
        println("WARNING: Use of the 'debug' instruction may potentially cause the VM to crash if it's not run in debug mode")
    }
}

class HltInstruction : NoOperandInstruction(HLT, "hlt")