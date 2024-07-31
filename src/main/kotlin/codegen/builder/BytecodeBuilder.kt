package cum.jesus.jesusasm.codegen.builder

import cum.jesus.jesusasm.codegen.ModuleBytecodeBuffer
import cum.jesus.jesusasm.codegen.OperandSize
import cum.jesus.jesusasm.codegen.Section

private class ForwardLabel(
    val name: String,
    val section: Section,
    val size: OperandSize,
    val location: Long,
    val origin: Long
)

/**
 * Builder class in charge of abstracting away the creation and usage of module files
 */
class BytecodeBuilder(val output: ModuleBytecodeBuffer, var moduleName: String) {
    var section: Section = Section.Bytecode

    private val forwardLabels = mutableListOf<ForwardLabel>()

    inline fun function(section: Section = Section.Functions, code: Function.() -> Unit) {
        val function = Function(output, section)
        function.code()
        function.emit()
    }

    inline fun constant(section: Section = Section.ConstPool, code: Constant.() -> Unit) {
        val constant = Constant(output, section)
        constant.code()
        constant.emit()
    }

    inline fun instruction(section: Section = Section.Bytecode, code: Instruction.() -> Unit) {
        val instruction = Instruction(output, section)
        instruction.code()
        instruction.emit()
    }

    fun patchForwardLabels() {
        for (label in forwardLabels) {
            output.patchForwardSymbol(label.name, label.section, label.size, label.location.toInt(), label.origin.toInt())
        }
    }

    fun addLabel(name: String, section: Section) {
        output.addSymbol(name, output.getPosition(section))
    }

    fun forwardLabel(name: String, section: Section, size: OperandSize, offset: Int = 0) {
        forwardLabels.add(ForwardLabel(name, section, size, output.getPosition(section) + offset, output.getPosition(section)))
    }

    fun getLabel(name: String) = output.getSymbol(name)

    fun getPosition(section: Section) = output.getPosition(section)
}