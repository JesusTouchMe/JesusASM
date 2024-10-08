package cum.jesus.jesusasm

import cum.jesus.jesusasm.codegen.ModuleBytecodeBuffer
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.lexer.Lexer
import cum.jesus.jesusasm.parser.Parser
import cum.jesus.jesusasm.printer.AsmPrinter
import java.io.BufferedOutputStream
import java.io.File
import java.io.FileOutputStream

fun main(args: Array<String>) {
    val input = File(args[0])

    val lexer = Lexer(input.readText())
    val tokens = lexer.lex()

    val parser = Parser(input.name, tokens)
    val values = parser.parse()
    val entry = parser.globalContext.constants[parser.metaData.entry]!!

    val asmPrinter = AsmPrinter(parser.metaData.module, values)
    asmPrinter.print(System.out)

    val output = ModuleBytecodeBuffer(parser.metaData.module, entry)
    val builder = BytecodeBuilder(output)

    for (value in values) {
        value.emit(builder, builder.section)
    }

    builder.patchForwardLabels()

    val outputFile = File(input.nameWithoutExtension + ".jmod")
    outputFile.delete()
    outputFile.createNewFile()

    val outputFileStream = FileOutputStream(outputFile, true)
    val outputStream = BufferedOutputStream(outputFileStream)

    output.print(outputStream)

    outputStream.flush()
}