package cum.jesus.jesusasm

import cum.jesus.jesusasm.lexer.Lexer
import java.io.File

fun main(args: Array<String>) {
    val input = File(args[0])

    val lexer = Lexer(input.readText())
    val tokens = lexer.lex()

    tokens.forEach {
        println(it)
    }
}