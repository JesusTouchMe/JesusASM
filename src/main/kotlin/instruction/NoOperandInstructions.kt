/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder

open class NoOperandInstruction(val opcode: Opcode) : Instruction {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.instruction(section) {
            opcode = this@NoOperandInstruction.opcode
        }
    }
}

class NopInstruction : NoOperandInstruction(NOP)
class PopInstruction : NoOperandInstruction(POP)
class DupInstruction : NoOperandInstruction(DUP)

class ALoadInstruction : NoOperandInstruction(ALOAD)
class AStoreInstruction : NoOperandInstruction(ASTORE)

class AddInstruction : NoOperandInstruction(ADD)
class SubInstruction : NoOperandInstruction(SUB)
class MulInstruction : NoOperandInstruction(MUL)
class DivInstruction : NoOperandInstruction(DIV)
class AndInstruction : NoOperandInstruction(AND)
class OrInstruction : NoOperandInstruction(OR)
class XorInstruction : NoOperandInstruction(XOR)

class IncInstruction : NoOperandInstruction(INC)
class DecInstruction : NoOperandInstruction(DEC)
class NotInstruction : NoOperandInstruction(NOT)
class NegInstruction : NoOperandInstruction(NEG)

class CmpInstruction : NoOperandInstruction(CMP)

class RetInstruction : NoOperandInstruction(RET)

class DebugInstruction : NoOperandInstruction(DEBUG) {
    init {
        println("WARNING: Use of the 'debug' instruction may potentially cause the VM to crash if it's not run in debug mode")
    }
}

class HltInstruction : NoOperandInstruction(HLT)