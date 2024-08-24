package cum.jesus.jesusasm.printer

import cum.jesus.jesusasm.instruction.*
import cum.jesus.jesusasm.instruction.Function
import java.io.PrintStream

class AsmPrinter(val module: String, val values: Collection<Value>) {
    fun print(stream: PrintStream) {
        stream.println(module)

        for (value in values) {
            when (value) {
                is Class, is Constant, is Directive, is Function -> {}

                is Label -> stream.print("  ")

                else -> stream.print("    ")
            }

            val res = value.print(stream)
            if (res) {
                stream.println()
            }
        }
    }
}