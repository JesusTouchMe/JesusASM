/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.parser

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.environment.FunctionContext
import cum.jesus.jesusasm.environment.GlobalContext
import cum.jesus.jesusasm.instruction.*
import cum.jesus.jesusasm.instruction.Function
import cum.jesus.jesusasm.lexer.Token
import cum.jesus.jesusasm.lexer.TokenType
import cum.jesus.jesusasm.type.Type
import cum.jesus.jesusasm.type.getFunctionType
import cum.jesus.jesusasm.type.getType
import kotlin.math.exp

class TokenStream (val tokens: List<Token>) {
    var position: Int = 0

    fun current() = tokens[position]

    fun consume() = tokens[position++]

    fun peek(offset: Int) = tokens[position + offset]

    fun expectToken(type: TokenType) {
        val token = current()
        if (token.tokenType != type) {
            println("error $token")
            throw RuntimeException()
        }
    }

    fun expectTokens(vararg types: TokenType) {
        val token = current()

        for (type in types) {
            if (token.tokenType == type) return
        }

        throw RuntimeException("error $token")
    }
}

class Parser(val fileName: String, tokens: List<Token>) {
    val metaData = MetaData()
    val globalContext = GlobalContext()
    var currentFunctionContext: FunctionContext? = null

    private val tokenStream = TokenStream(tokens)
    private val instructionParser = InstructionParser(tokenStream, globalContext)

    fun parse(): List<Value> {
        val values = mutableListOf<Value>()

        while (current().tokenType != TokenType.End) {
            val value = parseStatement()
            if (value != null) values.add(value)
        }

        return values
    }

    private fun parseStatement(): Value? {
        val token = current()

        when (token.tokenType) {
            TokenType.Error -> {
                println("error $token")
                throw RuntimeException()
            }

            TokenType.Dot -> {
                return parseDotStatement()
            }

            TokenType.Identifier -> {
                return parseLabel()
            }

            TokenType.Function -> {
                return parseFunction()
            }

            TokenType.Const -> {
                return parseConstant()
            }

            TokenType.Section -> {
                consume()
                return SectionDirective(consume().text)
            }

            TokenType.Instruction -> {
                return instructionParser.parse(currentFunctionContext)
            }

            else -> {
                throw RuntimeException("bad $token")
            }
        }
    }

    private fun parseDotStatement(): Value? {
        consume() // .

        val token = current()

        when (token.tokenType) {
            TokenType.Module -> {
                consume()
                expectToken(TokenType.String)

                metaData.module = consume().text

                return null
            }

            TokenType.Stack -> {
                consume()
                expectToken(TokenType.Immediate)

                var value = consume().text.toUInt()

                if (current().tokenType == TokenType.Identifier) {
                    when (current().text) {
                        "kb" -> value *= 1024u
                        "mb" -> value *= 1048576u
                        "gb" -> value *= 1073741824u
                    }

                    consume()
                }

                metaData.stack = value

                return null
            }

            TokenType.Entry -> {
                consume()
                expectToken(TokenType.String)

                metaData.entry = consume().text

                return null
            }

            TokenType.Locals -> {
                consume()
                expectToken(TokenType.Immediate)

                val value = consume().text.toUShort()

                if (currentFunctionContext == null) {
                    throw RuntimeException(".locals when a function hasn't been declared yet")
                }

                currentFunctionContext!!.locals = value

                return null
            }

            TokenType.Function -> {
                return parseConstantFunction()
            }

            else -> {
                throw RuntimeException("bad $token")
            }
        }
    }

    private fun parseType(): Type {
        expectToken(TokenType.Type)

        return getType(consume().text)!!
    }

    private fun parseLabel(): Value {
        val name = consume().text
        expectToken(TokenType.Colon)
        consume()

        return Label(name)
    }

    private fun parseFunction(): Value {
        consume() // function

        val modifiers = mutableListOf<Modifier>()

        while (current().tokenType != TokenType.Type) {
            expectTokens(TokenType.Public, TokenType.Private)
            val modifier = consume()

            when (modifier.tokenType) {
                TokenType.Public -> modifiers.add(Modifier.Public)
                TokenType.Private -> modifiers.add(Modifier.Private)

                else -> throw RuntimeException("unreachable")
            }
        }

        val returnType = parseType()

        expectToken(TokenType.Identifier)
        val name = consume().text

        expectToken(TokenType.LeftParen)
        consume()

        val argumentTypes = mutableListOf<Type>()

        currentFunctionContext = FunctionContext()

        while (current().tokenType != TokenType.RightParen) {
            val type = parseType()
            argumentTypes.add(type)

            if (current().tokenType != TokenType.RightParen) {
                expectToken(TokenType.Comma)
                consume()
            }
        }
        consume()

        expectToken(TokenType.Colon)
        consume()

        val type = getFunctionType(returnType, argumentTypes)
        return Function(name, type, modifiers)
    }

    private fun parseConstant(): Value {
        consume() // const

        expectToken(TokenType.String)
        val name = consume().text

        expectToken(TokenType.Equals)
        consume()

        globalContext.addConstant(name)

        return parseConstantValue()
    }

    private fun parseConstantValue(): Value {
        expectToken(TokenType.Dot)
        consume()

        val token = current()

        when (token.tokenType) {
            TokenType.Function -> {
                return parseConstantFunction()
            }

            else -> {
                throw RuntimeException("bad $token")
            }
        }
    }

    private fun parseConstantFunction(): Value {
        consume() // function

        val returnType = parseType()

        expectToken(TokenType.Identifier)

        val moduleParts = mutableListOf<String>()
        var name: String = "0"

        while (current().tokenType != TokenType.End) {
            if (current().tokenType == TokenType.Identifier) {
                val text = consume().text

                if (current().tokenType == TokenType.Slash) {
                    moduleParts.add(text)
                    consume()
                } else {
                    name = text
                    break
                }
            } else {
                throw RuntimeException("bad ${current()}")
            }
        }

        val module = moduleParts.joinToString("/")

        expectToken(TokenType.LeftParen)
        consume()

        val argumentTypes = mutableListOf<Type>()

        while (current().tokenType != TokenType.RightParen) {
            val type = parseType()
            argumentTypes.add(type)

            if (current().tokenType != TokenType.RightParen) {
                expectToken(TokenType.Comma)
                consume()
            }
        }
        consume()

        val functionType = getFunctionType(returnType, argumentTypes)
        return ConstantFunction(module, name, functionType)
    }

    private inline fun expectToken(type: TokenType) = tokenStream.expectToken(type)

    private inline fun expectTokens(vararg types: TokenType) = tokenStream.expectTokens(*types)

    private inline fun current() = tokenStream.current()

    private inline fun consume() = tokenStream.consume()

    private inline fun peek(offset: Int) = tokenStream.peek(offset)
}