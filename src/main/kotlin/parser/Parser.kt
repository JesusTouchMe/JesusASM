package cum.jesus.jesusasm.parser

import cum.jesus.jesusasm.instruction.Value
import cum.jesus.jesusasm.lexer.Token
import cum.jesus.jesusasm.lexer.TokenType

class TokenStream (val tokens: List<Token>) {
    var position: Int = 0

    fun current() = tokens[position]

    fun consume() = tokens[position++]

    fun peek(offset: Int) = tokens[position + offset]
}

class Parser(val fileName: String, tokens: List<Token>) {
    val tokenStream: TokenStream = TokenStream(tokens)

    fun parse(): List<Value> {
        val values = mutableListOf<Value>()

        while (current().tokenType != TokenType.End) {
            values.add(parseStatement())
        }

        return values
    }

    private fun parseStatement(): Value {
        val token = current()

        when (token.tokenType) {
            TokenType.Error -> {
                println("error $token")
                throw RuntimeException()
            }

            TokenType.Identifier -> {
                return parseLabel()
            }
        }
    }

    private fun parseLabel(): Value {

    }

    private fun parseDotStatement(): Value {

    }

    private fun expectToken(type: TokenType) {
        val token = current()
        if (token.tokenType != type) {
            println("error $token")
            throw RuntimeException()
        }
    }

    private inline fun current() = tokenStream.current()

    private inline fun consume() = tokenStream.consume()

    private inline fun peek(offset: Int) = tokenStream.peek(offset)
}