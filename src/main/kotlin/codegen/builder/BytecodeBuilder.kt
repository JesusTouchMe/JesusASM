/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

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
class BytecodeBuilder(val output: ModuleBytecodeBuffer) {
    var section: Section = "code"

    private val forwardLabels = mutableListOf<ForwardLabel>()
    private val strings = mutableMapOf<String, UInt>()

    inline fun function(section: Section = "functions", code: Function.() -> Unit) {
        val function = Function(output, section)
        function.code()
        function.emit()
    }

    inline fun clas(section: Section = "classes", code: Class.() -> Unit) {
        val clas = Class(output, section)
        clas.code()
        clas.emit()
    }

    inline fun constant(section: Section = "constpool", code: Constant.() -> Unit) {
        val constant = Constant(output, section)
        constant.code()
        constant.emit()
    }

    inline fun instruction(section: Section = "code", code: Instruction.() -> Unit) {
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

    fun getSection(name: String): Section = output.getSection(name)

    fun getString(string: String): UInt {
        return strings.getOrElse(string) {
            val index = output.getPosition("strtab").toUInt()
            strings[string] = index

            output.write(string.length.toUShort(), "strtab")
            output.write(string, "strtab")

            return index
        }
    }

    fun incFunctionCount() {
        output.functionCount++
    }

    fun incClassCount() {
        output.classCount++
    }

    fun incConstPoolElementCount() {
        output.constPoolElementCount++
    }
}