package cum.jesus.jesusasm.instruction.singleoperandinstruction

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.instruction.Instruction
import cum.jesus.jesusasm.instruction.operand.LabelOperand
import cum.jesus.jesusasm.util.getImmediateSize

open class BaseJmpInstruction(val opcode: Opcode, val label: LabelOperand? = null) : Instruction {
    override fun emit(builder: BytecodeBuilder, section: Section) {
        var wide: Boolean = false
        val value = label?.getValue(builder, section) ?: 0

        builder.instruction(section) {
             if (label != null) {
                 opcode = getRelativeOpcode()

                 immediate = (value - builder.getPosition(section)).toULong()

                 if (value == -1L || value - builder.getPosition(section) !in Byte.MIN_VALUE..Byte.MAX_VALUE) {
                     wide = true
                     prefix = WIDE
                     immediateSize = OperandSize.Int
                 } else {
                     wide = false
                     immediateSize = OperandSize.Byte
                 }
             } else {
                 opcode = this@BaseJmpInstruction.opcode
             }
        }

        if (label == null) return

        if (wide) {
            if (value == -1L) {
                label.forward(builder, section, OperandSize.Int, -4)
            }
        } else {
            if (value == -1L) {
                label.forward(builder, section, OperandSize.Byte, -1)
            }
        }
    }

    private fun getRelativeOpcode(): Opcode {
        return when (opcode) {
            JMP -> JMPREL
            JEQ -> JEQREL
            JNE -> JNEREL
            JLT -> JLTREL
            JGT -> JGTREL
            JLE -> JLEREL
            JGE -> JGEREL

            else -> throw RuntimeException("bad jump opcode $opcode")
        }
    }
}

class JmpInstruction(label: LabelOperand?) : BaseJmpInstruction(JMP, label)
class JeqInstruction(label: LabelOperand?) : BaseJmpInstruction(JEQ, label)
class JneInstruction(label: LabelOperand?) : BaseJmpInstruction(JNE, label)
class JltInstruction(label: LabelOperand?) : BaseJmpInstruction(JLT, label)
class JgtInstruction(label: LabelOperand?) : BaseJmpInstruction(JGT, label)
class JleInstruction(label: LabelOperand?) : BaseJmpInstruction(JLE, label)
class JgeInstruction(label: LabelOperand?) : BaseJmpInstruction(JGE, label)